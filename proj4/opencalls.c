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
  return open(filename, flags);
}

long fileDescriptorW (char* filename) {
  return open(filename, O_WRONLY, 0666);
}

size_t jread(long fd, void *buf, size_t cnt) {
  return read(fd, buf, cnt);
}

size_t jwrite(long fd, void *buf, size_t cnt) {
  return write(fd, buf, cnt);
}

size_t jfilesize(char *filename) {
  int fd = fileDescriptor(filename, O_RDONLY);
  if (fd < 0) return -1;
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

FILE* fpointer(char *filename, char *options) {
  return fopen(filename, options);
}

void jfopen(FILE *file) {
  fclose(file);
}

size_t jffilesize(FILE *file) {
  int count = 0;
  if(file) {
    for(char c = getc(file); c != EOF; c = getc(file)) {
      ++count;
    }
  } else {
    return -1;
  }
  return count;
}


void jfread(FILE *file, char* buf, int size) {
  if (file) {
    char c;
    int i;
    for (c=getc(file), i = 0; i < size && c != EOF; ++i, c = getc(file)) {
      buf[i] = c;
    }
  }
}

void jfwrite(FILE* file, char* buf) {
  if(file) {
    fprintf(file,"%s", buf);
  } 
}

