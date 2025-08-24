#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  // Student code goes here

  if (fork() == 0) {
    // for (int i = 0; i < argc; i++) {
    //   printf(1, "%s\t", argv[i]);
    // }
    exec("/echo", argv); // shortcut?
    exit(); // Good practice according to TAs.
  }
  wait(); // Prevent any zombies
  exit();
}