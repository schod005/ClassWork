#include <stdio.h>
#include <fcntl.h>

#define ITEMSIZE 32

int main(int argc, char **argv)
{
  int fd;
  int num_items;
  int i;

  if(argc != 2)
  {
    perror("Usage: ./consumer <number_items>\n");
    return 0;
  }

  if((fd = open("/dev/scullbuffer", O_RDONLY)) == -1)
  {
    perror("Cannot open scullbuffer for writing\n");
    return 0;
  }

  char array[ITEMSIZE];

  num_items = atoi(argv[1]);
  for(i = 0; i < num_items; i++)
  {
    if(read(fd, array, ITEMSIZE) == 0)
    {
      printf("Nothing to read\n");
      return 0;
    }
    else
      printf("Reading item %s\n", array);
    usleep(100000); //sleep for 100ms
  }

  close(fd);
}
