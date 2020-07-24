## Time of the executions

The first project is relatively slow. This is because I am reading and writing to a 1 byte pipe. So the operating system has to go into kernel mode, move the one singular byte to the pipe, and then go back to user mode. Then it has to go into kernel mode to read the byte, and it has to do this for every single bite in the file. On my Intel i7 laptop with 32 GB of RAM running OS X 10.13, it finished reading the `anna.txt` file in 2 seconds of kernel mode, and 0.4 in user mode. Which is very slow for a few megabytes.

The second project is much faster. This is because I am requesting a large number of memory pages in the shared memory part of the OS. This is all done in 0.007 seconds of kernel mode. Then I am reading it out, and this takes the 0.13 seconds in user mode. It does spawn threads, but the threads currently I cannot get to modify shared memory only read. If we had 4 threads properly implemented, I believe it would've run magnitudes faster than the first subproject, as I would be completing syscalls much more infrequently.