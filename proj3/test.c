#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  unsigned long PAGE_SIZE = sysconf(_SC_PAGESIZE);
  // Flags
	unsigned long VM_READ		= 0x00000001;	/* currently active flags */
	unsigned long VM_WRITE	= 0x00000002;
	unsigned long VM_EXEC		= 0x00000004;
	unsigned long VM_SHARED	= 0x00000008;

	/* mprotect() hardcodes VM_MAYREAD >> 4 == VM_READ, and so for r/w/x bits. */
  long limit = 4*PAGE_SIZE;
  long adresses[] = {
    (long)syscall, //1
    (long)&main,    //2
    (long)&sysconf, //3
    (long)&argc,    //4
    (long)&argv,    //5
    (long)&VM_READ, //6
    (long)&VM_WRITE,//7
    (long)&VM_EXEC, //8
    (long)&VM_SHARED/*9*/,
    (long)&printf,  //10
    (long)&limit,   //11
    (long)&adresses,//12
    (long)&PAGE_SIZE//13
  };
  for (int j = 0; j < 13; ++j) {
    for (long i = adresses[j]; i < adresses[j]+limit; i += PAGE_SIZE) {
      unsigned long memflags = syscall(334, i); 
      if (memflags == -1) {
        printf("Memory address: 0x%lx(FLAGS: 0x%lx) is unaccessable\n", i, memflags);
        continue;
      }
      printf("Memory address 0x%lx(FLAGS: 0x%lx) is: ", i, memflags);
      if (memflags && VM_READ) printf("readable, ");
      else printf("not readable, ");
      if (memflags && VM_WRITE) printf("writable, ");
      else printf("not writable, ");
      if (memflags && VM_EXEC) printf("and execuatable.");
      else printf("and not executable.");
      printf("\n");
    }
  }
  return 0;
}
