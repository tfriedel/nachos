#include "syscall.h"

int main(int argc, char **argv)
{
  OpenFileId fd;
  int num_read;
  char buffer;

  fd = Open(argv[1],RO);

  if (fd<0)
    Exit(-1);
  
  do
  {
    num_read = Read(fd, &buffer, 1);
    
    if (num_read > 0)
      Write(ConsoleOutput, &buffer, 1);
  } while (num_read > 0);
  
  Close(fd);
}
