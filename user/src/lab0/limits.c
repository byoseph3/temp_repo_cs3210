#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096  // 4K Page size

int
main(int argc, char *argv[])
{
  // Student code goes here
  int pages = 0;

  while (sbrk(PGSIZE) != (void *) -1) { // had to cast this because make wsa complaining.
    pages++;
  }
  
  printf(1, "Maximum Memory Size: 0x%x\n", pages * PGSIZE);
  exit();
}