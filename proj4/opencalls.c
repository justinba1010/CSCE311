/* Copyright 2019
 * Justin Baum
 * 1 December 2019
 * CSCE311
 * opencalls.cc
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define STANDARDBUFFERSIZE 1024

long fileDescriptor (char* filename, long flags) {
  return open(filename, flags | O_CREAT);
}

size_t jread(long fd, void *buf, size_t cnt) {
  return read(fd, buf, cnt);
}

size_t jfilesize(char *filename) {
  int fd = fileDescriptor(filename, O_RDONLY);
  char buffer[STANDARDBUFFERSIZE];
  size_t count = 0;
  size_t sizeRead = STANDARDBUFFERSIZE;
  while (sizeRead == STANDARDBUFFERSIZE) {
    sizeRead = jread(fd, buffer, STANDARDBUFFERSIZE);
    count += sizeRead;
  }
  close(fd);
  return count;
}
