/**
 *
 * David Schoder
 * 4552990
 *
 * buffer.c
 *
 * This is a simple character buffer that allows for concurrnet reads and writes.
 *
 * Most of the code is reused from scullpipe.  Alterations were made to convert
 * from a pipe to a buffer.
 *
 **/
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>	/* printk(), min() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/proc_fs.h>
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/fcntl.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include "scull.h"		/* local definitions */

#define init_MUTEX(_m) sema_init(_m, 1);
#define ITEMSIZE 32

static ssize_t scull_buffer_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
static ssize_t scull_buffer_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);
static int scull_buffer_open(struct inode *inode, struct file *filp);
static int scull_buffer_release(struct inode *inode, struct file *filp);

/*
 * The file operations for the pipe device
 * (some are overlayed with bare scull)
 */
struct file_operations scull_buffer_fops = {
	.owner =	THIS_MODULE,
	.read =		scull_buffer_read,
	.write =	scull_buffer_write,
	.open =		scull_buffer_open,
	.release =	scull_buffer_release,
};

struct scull_buffer {
        char *buffer;                      /* begin of buf */
        int buffersize;                    /* used in pointer arithmetic */
        char *rp, *wp;                     /* where to read, where to write */
        int nreaders, nwriters;            /* number of openings for r/w */
        struct semaphore sem;              /* mutual exclusion semaphore */
        struct cdev cdev;                  /* Char device structure */
};

/* parameters */
int NITEMS = 20;
dev_t scull_buffer_devno;			/* Our first device number */

module_param(NITEMS, int, 0);

static struct scull_buffer *scull_buffer_device;

static int spacefree(struct scull_buffer *dev);

/*
 * Open and close
 * should only change nreaders/nwriters in scull_buffer
 */
static int scull_buffer_open(struct inode *inode, struct file *filp)
{
	struct scull_buffer *dev;

	dev = container_of(inode->i_cdev, struct scull_buffer, cdev);
	filp->private_data = dev;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	/* use f_mode,not  f_flags: it's cleaner (fs/open.c tells why) */
	if (filp->f_mode & FMODE_READ)
		dev->nreaders++;
	if (filp->f_mode & FMODE_WRITE)
		dev->nwriters++;
	up(&dev->sem);

	return 0;
}

static int scull_buffer_release(struct inode *inode, struct file *filp)
{
	struct scull_buffer *dev = filp->private_data;

	down(&dev->sem);
	if (filp->f_mode & FMODE_READ)
		dev->nreaders--;
	if (filp->f_mode & FMODE_WRITE)
		dev->nwriters--;
	up(&dev->sem);
	return 0;
}

/*
 * Data management: read and write
*/
static ssize_t scull_buffer_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct scull_buffer *dev = filp->private_data;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	PDEBUG("\" (scull_buffer_read) dev->wp:%p    dev->rp:%p\" \n",dev->wp,dev->rp);

	while (dev->rp == dev->wp) { /* nothing to read */
    //if there are no writers, don't wait
    if(dev->nwriters == 0)
    {
      up(&dev->sem);
      return 0;
    }
		up(&dev->sem); /* release the lock */
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		PDEBUG("\"%s\" reading: going to sleep\n", current->comm);
		/* otherwise loop, but first reacquire the lock */
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}
	/* ok, data is there, return something */
	if (dev->wp > dev->rp)
		count = min(count, (size_t)(dev->wp - dev->rp));
	else /* the write pointer has wrapped, return data up to dev->end */
		count = min(count, (size_t)(dev->buffer + dev->buffersize - dev->rp));
	if (copy_to_user(buf, dev->rp, count)) {
		up (&dev->sem);
		return -EFAULT;
	}
	dev->rp += count;
	if (dev->rp == dev->buffer + dev->buffersize)
		dev->rp = dev->buffer; /* wrapped */
	up (&dev->sem);

	PDEBUG("\"%s\" did read %li bytes\n",current->comm, (long)count);
	return count;
}

/* How much space is free? */
static int spacefree(struct scull_buffer *dev)
{
	if (dev->rp == dev->wp)
		return dev->buffersize - 1;
	return ((dev->rp + dev->buffersize - dev->wp) % dev->buffersize) - 1;
}

static ssize_t scull_buffer_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct scull_buffer *dev = filp->private_data;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	while (spacefree(dev) == 0) { /* full */
    //if there are no readers, don't even wait
    if(dev->nreaders == 0)
    {
      up(&dev->sem);
      return 0;
    }
		up(&dev->sem); /* release the lock */
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		PDEBUG("\"%s\" writinging: going to sleep\n", current->comm);
		/* otherwise loop, but first reacquire the lock */
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}

	/* ok, space is there, accept something */
	count = min(count, (size_t)spacefree(dev));
	if (dev->wp >= dev->rp)
		count = min(count, (size_t)(dev->buffer + dev->buffersize - dev->wp)); /* to end-of-buf */
	else /* the write pointer has wrapped, fill up to rp-1 */
		count = min(count, (size_t)(dev->rp - dev->wp - 1));
	PDEBUG("Going to accept %li bytes to %p from %p\n", (long)count, dev->wp, buf);
	if (copy_from_user(dev->wp, buf, count)) {
		up (&dev->sem);
		return -EFAULT;
	}
	dev->wp += count;
	if (dev->wp == dev->buffer + dev->buffersize)
		dev->wp = dev->buffer; /* wrapped */
	PDEBUG("\" (scull_p_write) dev->wp:%p    dev->rp:%p\" \n",dev->wp,dev->rp);
	up(&dev->sem);

	PDEBUG("\"%s\" did write %li bytes\n",current->comm, (long)count);
	return count;
}


/*
 * Set up a cdev entry.
 */
static void scull_buffer_setup_cdev(struct scull_buffer *dev)
{
	int err;
    
	cdev_init(&dev->cdev, &scull_buffer_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add (&dev->cdev, scull_buffer_devno, 1);
	/* Fail gracefully if need be */
	if (err)
		printk(KERN_NOTICE "Error %d adding scullbuffer", err);
}

/*
 * Initialize the buffer devs; return how many we did.
 */
int scull_buffer_init(dev_t firstdev)
{
	int result;

	result = register_chrdev_region(firstdev, 1, "scullbuffer");
	if (result < 0) {
		printk(KERN_NOTICE "Unable to get scullbuffer region, error %d\n", result);
		return 0;
	}
	scull_buffer_devno = firstdev;
  scull_buffer_device = kmalloc(sizeof(struct scull_buffer), GFP_KERNEL);
	if (scull_buffer_device == NULL) {
		unregister_chrdev_region(firstdev, 1);
		return 0;
	}
	memset(scull_buffer_device, 0, sizeof(struct scull_buffer));

  //set up everything inside scull buffer
	scull_buffer_device->buffer = kmalloc(ITEMSIZE * sizeof(char) * NITEMS , GFP_KERNEL);

  scull_buffer_device->nreaders = 0;
  scull_buffer_device->nwriters = 0;
  scull_buffer_device->buffersize = ITEMSIZE * sizeof(char) * NITEMS;
  scull_buffer_device->rp = scull_buffer_device->buffer;
  scull_buffer_device->wp = scull_buffer_device->buffer;

  sema_init(&scull_buffer_device->sem, 1);
  scull_buffer_setup_cdev(scull_buffer_device);

	return 1;
}

/*
 * This is called by cleanup_module or on failure.
 * It is required to never fail, even if nothing was initialized first
 */
void scull_buffer_cleanup(void)
{
	if (!scull_buffer_device)
		return; /* nothing else to release */

  kfree(scull_buffer_device->buffer);
	kfree(scull_buffer_device);
	unregister_chrdev_region(scull_buffer_devno, 1);
	scull_buffer_device = NULL; /* pedantic */
}

