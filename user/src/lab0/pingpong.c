#include "types.h"
#include "stat.h"
#include "user.h"

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

  pipe(p_ptoc);
  pipe(p_ctop);
  child_checker = fork();
  pid = getpid();

  if (!child_checker) {
    // child code
    pid = getpid();
    printf(1, "Child pid: %d\n", pid); // for debugging

    close(p_ptoc[1]); // close off input segment of the parent to child pipe.
    close(p_ctop[0]); // close off output segment of the chlid to parent pipe.

    read(p_ptoc[0], buf, 1);
    printf(1, "child: received ping from %d\n", *buf);

    // child sends pid
    write(p_ctop[1], &pid, 1);

    exit(); // good practice to exit children.
  }
  // parent code
  pid = getpid();
  printf(1, "Parent pid: %d\n", pid); // for debugging

  close(p_ptoc[0]); // close off output segment of the parent to child pipe.
  close(p_ctop[1]); // close off input segment of the child to parent pipe.

  // parent sends pid
  write(p_ptoc[1], &pid, 1);

  // waits to receive pid from child
  read(p_ctop[0], buf, 1);
  printf(1, "parent: received pong from %d\n", *buf);

  wait(); // no zombies
  exit();
}