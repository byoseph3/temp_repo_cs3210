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

int
main(int argc, char *argv[])
{
  // Student code goes here
  // TODO: still need to figure out how to set up blocker. read() == 0?

  int p_ptoc[2]; // pipe for parent to child
  int p_ctop[2]; // pipe for child to parent
  int pid; // For both parent and child.
  char buf[1]; // to hold the pid values.
  int child_checker; // if 0, clearly in child process. (Used to make code easier to write)
  int err = 0;

  err = pipe(p_ptoc);
  err_checker_helper(err, "Error when creating pipe 1.\n");
  err = pipe(p_ctop);
  err_checker_helper(err, "Error when creating pipe 2.\n");
  child_checker = fork();
  pid = getpid();

  if (!child_checker) {
    // child code
    pid = getpid();

    err = close(p_ptoc[1]); // close off input segment of the parent to child pipe.
    err_checker_helper(err, "Error when closing off input segment of pipe 1.\n");
    err = close(p_ctop[0]); // close off output segment of the chlid to parent pipe.
    err_checker_helper(err, "Error when closing off output segment of pipe 2.\n");

    err = read(p_ptoc[0], buf, 1);
    err_checker_helper(err, "Error when reading from pipe 1.\n");

    printf(1, "child: received ping from %d\n", *buf);

    // child sends pid
    err = write(p_ctop[1], &pid, 1);
    err_checker_helper(err, "Error when writing to pipe 2.\n");

    exit(); // good practice to exit children.
  }
  // parent code
  pid = getpid();

  err = close(p_ptoc[0]); // close off output segment of the parent to child pipe.
  err_checker_helper(err, "Error when closing off output segment of pipe 1.\n");
  err = close(p_ctop[1]); // close off input segment of the child to parent pipe.
  err_checker_helper(err, "Error when closing off input segment of pipe 2.\n");

  // parent sends pid
  err = write(p_ptoc[1], &pid, 1);
  err_checker_helper(err, "Error when writing into pipe 1.\n");

  // waits to receive pid from child
  err = read(p_ctop[0], buf, 1);
  err_checker_helper(err, "Error when reading from pipe 2.\n");

  printf(1, "parent: received pong from %d\n", *buf);

  wait(); // no zombies
  exit();
}