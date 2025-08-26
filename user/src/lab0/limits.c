#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096  // 4K Page size

void
err_checker_helper(int err, char* msg)
{
  if (err != -1)
    return;
  
  printf(2, msg);
  return;
}

void
h_maxForkFinder(int i)
{
  int fork_num = fork();
  if (fork_num == -1) {
    // base case
    printf(1, "Maximum Number of Processes: %d\n", i);
    exit();
  } else if (fork_num == 0) {
    h_maxForkFinder(i+1);
    wait();
    exit();
  }
  wait();
}


int
main(int argc, char *argv[])
{
  // maximum processes
  // need to figure out how to tell when I'm out of proc memory
  // fork() will return -1!

  // Function below counts the maximum number of forks
  // as long as the number of non-fork processes are counted and used as the parameter,
  // the output should be correct.

  // Calculation is as follows:
  // forks that can be open: 61
  // limits.c creates a process: 1
  // init.c also execs sh.c: 2
  // 2 + 1 = 3
  // 3 + 61 = 64

  h_maxForkFinder(3); // 1 includes the current process.

  // maximum files
  // need to figure out how to tell when I'm out of file memory
  // need to figure out how to delete all files.

  // Calculation is as follows:
  // Number of files that can be opened as is: 14
  // File descriptors 0, 1, and 2 are taken by default, hence 3 more files are opened.
  // 14 + 3 = 17.

  int fd = open("file", O_CREATE);
  int file_counter = 4; // 4 counting file descriptors 0, 1, and 2. Also includes the file that was just created.
  int lowest_fd = fd;

  do {
    fd = open("file", O_CREATE);
    file_counter++;
  } while (fd != -1);

  for (int i = lowest_fd; i < fd; i++) {
    close(fd); // optional?
    unlink("file");
  }
  printf(1, "Maximum Number of Files Per Directory: %d\n", file_counter);

  // Student code goes here
  int pages = 0;

  int mallocFlag = 0;
  if (!mallocFlag) {
    while (sbrk(PGSIZE) != (void *) -1) { // had to cast this because make wsa complaining.
      pages++;
    }
  } else {
    while (malloc(PGSIZE) != 0) { // had to cast this because make wsa complaining.
      pages++;
    }
    //sbrk(-pages * PGSIZE);
  }
  
  printf(1, "Maximum Memory Size: 0x%x\n", pages * PGSIZE);
  exit();
}