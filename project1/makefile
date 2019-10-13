CC = g++-9

FLAGS = -Wall -std=c++11
FLAGS2 = $(FLAGS) -pedantic -pthread

LINK = $(CC) $(FLAGS) -o
COMPILE = $(CC) $(FLAGS) -c
COMPILE_LINUX = g++ $(FLAGS2) -c

SOCKET = socket_justin


server : server.o
	$(LINK) $@ $^
server.o : server.cc
	$(COMPILE) $<
client : client.o
	$(LINK) $@ $^
client.o : client.cc
	$(COMPILE) $<
project.o : project.cc
	$(COMPILE) $<
project : project.o
	$(LINK) $@ $^
project2.o : project2.cc
	$(COMPILE) $<
project2 : project2.o
	$(LINK) $@ $^
project2-new.o : project2-new.cc
	$(COMPILE) $<
project2-new : project2-new.o
	$(LINK) $@ $^
project2-linux :
	$(COMPILE_LINUX) project2-new.cc
	g++ $(FLAGS2) -o project2-new project2-new.o
