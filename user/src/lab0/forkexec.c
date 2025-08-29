#include "types.h"
#include "stat.h"
#include "user.h"

void
err_checker_helper(int err, char* msg)
{
  if (err != -1)
    return;
  
  printf(2, msg);
  return;
}

// weird error when running forkexec hello world
// Potentially too many characters??? Maybe some issue with output pointer???

int
main(int argc, char *argv[])
{
  // Student code goes here
  int err = 0;

  if (fork() == 0) {

    // 8 arguments is the max!
    err = exec("/echo", argv); // shortcut?
    err_checker_helper(err, "Error while child process is running echo\n");

    exit(); // Good practice according to TAs.
  }
  err = wait(); // Prevent any zombies
  err_checker_helper(err, "Wait failed. No child processes detected.");
  exit();
}