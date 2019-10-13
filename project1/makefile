CC = g++-9

FLAGS = -Wall -std=c++11

LINK = $(CC) $(FLAGS) -o
COMPILE = $(CC) $(FLAGS) -c

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
all: server client
	./server $(SOCKET)& ./client $(SOCKET)&
