#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

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
  char buf[13]; // Just enough to read "Hello World!\n"
  int fd_tmp; // for the temporary file descriptor
  int err = 0; // Used for error checking.

  /*if (fork() == 0) {
    fd_tmp = open("tmp.txt", O_CREATE|O_WRONLY);  // make is complaining that the correct flag is O_CREATE
                                                  // TO WRITE INTO THE FILE, MUST USE BOTH FLAGS
    if (fd_tmp < -1) {
      fprintf(2, "");
    }
    write(fd_tmp, "Hello World!\n", 13);
    close(fd_tmp);  // resetting the pointer by closing and opening (Advice from TA)
                    // Both read and write offset the pointer without resetting.
    fd_tmp=open("tmp.txt", O_RDONLY);
    read(fd_tmp, buf, 13);
    write(1, buf, 13); // display 13 bytes.
    close(fd_tmp);
    exit();
  }
  wait();*/
  fd_tmp = open("tmp.txt", O_CREATE|O_WRONLY);
  err_checker_helper(fd_tmp, "Error creating and opening tmp.txt\n");

  err = write(fd_tmp, "Hello World!\n", 13);
  err_checker_helper(err, "Error writing into tmp.txt\n");

  err = close(fd_tmp);
  err_checker_helper(err, "Error while closing tmp.txt\n");

  fd_tmp=open("tmp.txt", O_RDONLY); // to reset the file pointer to read the file
  err_checker_helper(err, "Error opening tmp.txt after closing\n");

  err = read(fd_tmp, buf, 13);
  err_checker_helper(err, "Error while reading from\n");

  err = write(1, buf, 13); // display 13 bytes.
  err_checker_helper(err, "Error while printing contents of tmp.txt\n");

  err = unlink("tmp.txt");
  err_checker_helper(err, "Error while unlinking/deleting tmp.txt\n");

  err = close(fd_tmp);
  err_checker_helper(err, "Error while closing tmp.txt after deletion\n");

  exit();
}