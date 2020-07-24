CC = gcc
FLAGS = -std=c99
LINK = $(CC) $(FLAGS) -o
COMPILE = $(CC) $(FLAGS) -c

driverp4 : driver.o
	$(LINK) $@ $^
driverp4.o : driver.c
	$(COMPILE) $<

tarball :
	tar cvf baum.tar.gz driver.c readme.md opencalls.c makefile report.md video.mov
