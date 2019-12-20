/* Copyright 2019
 * Justin Baum
 * 1 December 2019
 * CSCE311
 * driver.cc
*/
#include <stdlib.h>
#include <fcntl.h>
#include "opencalls.c"
#include <sys/mman.h>

void flipBuf(char *buf, size_t size);

int main(int argc, char *argv[]) {
  if (argc != 3) return 255;
  // Subproject 1.1 Using open/write/read
  if (argv[1][0] == '1') {
    size_t fileSize = jfilesize(argv[2]);
    if(fileSize <= 0) return -1;
    char buf[fileSize];
    long fd = fileDescriptor(argv[2], O_RDONLY | O_CREAT);
    jread(fd, buf, fileSize);
    close(fd);
    flipBuf(buf, fileSize);
    fd = fileDescriptorW(argv[2]);
    long x = jwrite(fd, buf, fileSize);
    close(fd);
    if (x) return -1;
  }
  // Subproject 1.2 Using 
  else if (argv[1][0] == '2') {
    FILE * file = fpointer(argv[2], "r");
    int fileSize = jffilesize(file);
    if(fileSize <= 0) return -1;
    char buf[fileSize];
    fseek(file, 0, SEEK_SET);
    jfread(file, buf, fileSize);
    rewind(file);
    fclose(file);
    file = fpointer(argv[2], "w");
    rewind(file);
    flipBuf(buf, fileSize);
    /*printf("%s", buf);*/
    jfwrite(file, buf);
  } else if (argv[1][0] == '3') {
    int fd = open(argv[2], O_RDWR);
    struct stat mystat;
    if (fstat(fd, &mystat)) {
      return 0x0f;
    }
    off_t myfsz = mystat.st_size;
    char *ad = mmap(NULL, myfsz, PROT_READ | PROT_WRITE, 
        MAP_SHARED, fd, 0);
    if (ad == NULL) return 0x1f;
    flipBuf(ad, myfsz);
    close(fd);
    munmap(ad, myfsz);
  }
  return 0;
}


void flipBuf(char *buf, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (buf[i] >=65 && buf[i] <= 90) buf[i] += 32;
    else if (buf[i] >=97 && buf[i] <= 122) buf[i] -= 32;
  }
}
