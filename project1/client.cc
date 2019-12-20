// Justin Baum
// Project 1
// CSCE311: Zeng
// 26 September 2019

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;


int main (int argc, char **argv) {
  struct sockaddr_un address;
  char buf[100];
  char *socket_path_name;
  int rc, cl;

  // Get path name from system arguments
  if (argc > 1) {
    socket_path_name=argv[1];
  } else {
    cout << "No socket name given" << endl;
    return -1;
  }
  // Get a socket
  int s = socket(AF_UNIX, SOCK_STREAM, 0);
  // Check if socket failed
  if (s == -1) {
    cout << "System failed" << endl;
    return 1;
  }

  // Blank out addr
  memset(&address, 0, sizeof(address));

  // Set address
  strncpy(address.sun_path, socket_path_name, sizeof(address.sun_path));
  address.sun_family = AF_UNIX;

  bind(s, (struct sockaddr*)&address, sizeof(address));

  while (1) {
    for (int i = 0; i < 100; i++) {
      buf[i] = 67;
    }
    write(s, buf, rc);
    
    if (rc == -1) {
      cout << "Read error?" << endl;
    }
    if (rc == 0) {
      cout << "EOF" << endl;
      close(cl);
      return 0;
    }
  }

  // Check if socket

  cout << s << endl;
  return 0;
}
