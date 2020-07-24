CSCE311
Project 4 Report
Justin Baum
5 December 2019

1. What is /proc in Linux/Unix? What does (cat /proc/$pid/maps) output, and how does it relate to Project 3? Please enumerate three other functions that you like most.
* /proc is a special file system, where Linux/Unix will keep information about processes. It isn't a real file system, instead it's a virtual file system. Where the kernel will handle accessing the information instead of the information being on disc. It contains all the processes running, and information relevant to each process. It is relevant for project 3, because it will contain the information necessary for the syscall and return. For project 4, it contains the file descriptors and information that the kernel will need to deal with such.
* `dmesg` had functionality I never knew about before. It tells us what is logged at the kernel level.
* `syscall` allows us to directly make a system call. I thought that was really cool, and this class was extremely interesting to me in that aspect.
* `fthread` gives us the option to spawn new threads. I really like the idea of optimizing multithreaded applications, and would love to learn more about hyperthreading and multicore functionality.

2. What is a Loadable Kernel Module?
* A loadable kernel module is a binary object file that can be dynamically added to the kernel, without recompiling the entire kernel. It is mostly used for adding new hardware, and/or new file systems and drivers. It makes it easy to swap out functionality and such, and reduces the amount of time needed to compile the entire Linux/Unix kernel. The main drawback is that they are not userspace programs. They are run at the kernel level, and such can make a system unstable.

3. Compare the three sets of APIs for I/O used in the first sub-project. Compare file descriptor, File pointer, file descriptor structure, and open file description.
* The first is directly through a system call. The first was `open` which allowed us to get a file descriptor as an integer. This file descriptor is used by the kernel to identify the file in question. The second `read` and `write` allow us to copy a certain number of bytes to an address space. I chose to use an array of `char` because it was easy to measure the number of bytes, but we could've requested a `void *` with mmap, and the latter allows us to copy from an address space directly back to a file.
* The second subprogram used `fopen` to return a `FILE` pointer. I am not too sure of how `libc` handles all of it, but it's just a wrapper from above. It includes `fputc` and `fgetc` which are essential to reading and writing files with this functionality. It is supposed to make reading and writing files easier, but I prefer the direct calls, it was easier to understand.
* The third problem used `mmap` to directly map a file to memory. This was the coolest feature, I didn't know Linux was capable of such. But frankly I believe it would probably be the fastest of the 3. The API I used was it was a direct memory map, so I casted the `void *` it returned as `char *` to make management easier on my side, then I modified it within memory. 
