#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define ITEMSIZE 32

int main(int argc, char **argv)
{
  int fd;
  int num_items;
  int i;

  if(argc != 2)
  {
    perror("Usage: ./producer <number_items>\n");
    return 0;
  }

  if((fd = open("/dev/scullbuffer", O_WRONLY)) == -1)
  {
    perror("Cannot open scullbuffer for writing\n");
    return 0;
  }

  char array[ITEMSIZE];

  num_items = atoi(argv[1]);
  for(i = 0; i < num_items; i++)
  {
    sprintf(array, "%032d", i);
    printf("Writing item %s\n", array);
    if(write(fd, array, ITEMSIZE) == 0)
    {
      printf("Write failed\n");
      return 0;
    }
    usleep(100000); // sleep for 100ms
  }

  close(fd);
}
