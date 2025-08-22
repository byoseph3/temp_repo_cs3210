#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  // Student code goes here
  char buf[13]; // Just enough to read "Hello World!\n"

  if (fork() == 0) {
    close(0); // Need to utilize a fork so that we can know for a fact that fd is 0.
              //Write and Close only take an fd (which is an integer).
    open("tmp.txt", O_CREATE); // make is complaining that the correct flag is O_CREATE
    write(0, "Hello World!\n", 13);
    read(0, buf, 13);
    write(1, buf, 13); // display 13 bytes.
    close(0);
  }
  
  exit();
}