/* Copyright 2019
 * Justin Baum
 * 1 December 2019
 * CSCE311
 * driver.cc
*/
#include <stdlib.h>
#include "opencalls.c"

int main(int argc, char *argv[]) {
  size_t fileSize = jfilesize(argv[1]);
  printf("The file %s is %zu bytes long\n", argv[1], fileSize);
  char buf[fileSize];
  long fd = fileDescriptor(argv[1], O_RDONLY | O_CREAT);
  jread(fd, buf, fileSize);
  close(fd);
  printf("The contents are: \n%s\n", buf);
  return 0;
}

