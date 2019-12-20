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
all: server client
	./server $(SOCKET)& ./client $(SOCKET)&
