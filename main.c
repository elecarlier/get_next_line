#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
  int    fd;
  char  *next_line;
  int  count;
  int i;

  i = 0;

  count = 0;
  fd = open("text.txt", O_RDONLY);
   if (fd == -1)
 {
   printf("Error opening file");
  return (1);
 }
  while (i < 2)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
      break ;
    count++;
    printf("[%d]:%s\n", count, next_line);

    next_line = NULL;
    i++;
  }
  close(fd);
  return (0);
}
