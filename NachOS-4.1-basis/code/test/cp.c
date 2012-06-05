#include "syscall.h"

int main(int argc, char **argv)
{
  OpenFileId src, dest;
  int num_read;
  char buffer;
  
  Create(argv[2]);
  
  src = Open(argv[1],RO);
  dest = Open(argv[2],RW);
  DebugString(argv[0],0);
  DebugString(argv[1],0);
  DebugString(argv[2],0);
  if ((src<0) || (dest<0))
    Exit(-1);
  
  do
  {
    num_read = Read(src, &buffer, 1);

    if (num_read > 0)
      Write(dest, &buffer, 1);
  }while (num_read > 0);
  
  Close(src);
  Close(dest);
}
