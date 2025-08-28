#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define PGSIZE 4096  // 4K Page size

void
h_maxForkFinder(int i)
{
  int fork_num = fork();
  if (fork_num == -1) {
    // base case (requires an error, so error is handled by default)
    printf(1, "Maximum Number of Processes: %d\n", i);
    exit(); // clean up
  } else if (fork_num == 0) {
    h_maxForkFinder(i+1);
    wait(); // clean up
    exit();
  }
  wait(); // make sure that this current process doesn't exit!
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

  // =====================================================
  // Calculation is as follows:
  // forks that can be open: 61
  // limits.c creates a process: 1
  // init.c also execs sh.c: 2
  // 2 + 1 = 3
  // 3 + 61 = 64
  // =====================================================

  h_maxForkFinder(3); // 1 includes the current process.

  // maximum files
  // need to figure out how to tell when I'm out of room in fd table.

  // =====================================================
  // Calculation is as follows:
  // Number of files that can be opened as is: 13
  // File descriptors 0, 1, and 2 are taken by default, hence 3 more files are opened.
  // 13 + 3 = 16.
  // Possible edge case is that the first file can't be created.
  // =====================================================

  // plan: since stdin, stdout, stderr count as files, keep opening files until maximum number is reached, then add 1 to account for stdin being 0.
  int fd;
  int min_fd = -1; // This is here for cleaning up after this limit test.
  int max_fd = -2; // This is to store the max file descriptor when fd becomes -1.
  while(fd != -1) {
    fd = open("file", O_CREATE);
    if (min_fd == -1) // Error handling is implicit due to final condition.
      min_fd = fd; // assign the lowest fd
    if (fd > max_fd)
      max_fd = fd; // Set max_fd
  }

  printf(1, "Maximum Number of Files Open at Once: %d\n", max_fd + 1); // adding 1 to account for stdin having fd 0.

  for (int i = min_fd; i < fd; i++) {
    close(fd); // optional?
    unlink("file"); // clean up!
  }

  // Student code goes here
  int pages = 0;

  int mallocFlag = 0;
  if (!mallocFlag) {
    while (sbrk(PGSIZE) != (void *) -1) { // had to cast this because make wsa complaining.
      pages++; // Error is being handled implicitly as it is the ending condition.
    }
    sbrk(-pages * PGSIZE); // clean up!
  } else {
    while (malloc(PGSIZE) != 0) { // had to cast this because make wsa complaining.
      pages++;
    }
  }
  
  printf(1, "Maximum Memory Size: 0x%x\n", pages * PGSIZE);
  exit();
}