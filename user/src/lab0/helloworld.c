#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  // Student code goes here
  char buf[13]; // Just enough to read "Hello World!\n"
  int fd_tmp; // for the temporary file descriptor
  char *rm_argv[2]; // to execute the command that will delete the temp file
  rm_argv[0] = "rm";
  rm_argv[1] = "tmp.txt";
  //int err;

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
  write(fd_tmp, "Hello World!\n", 13);
  close(fd_tmp);
  fd_tmp=open("tmp.txt", O_RDONLY);
  read(fd_tmp, buf, 13);
  write(1, buf, 13); // display 13 bytes.
  close(fd_tmp);
  exec("/rm", rm_argv);
  exit();
}