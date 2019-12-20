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

#define SOCK_PATH "our_socket"


int main (int argc, char **argv) {
  int s, s2, t, len;
  struct sockaddr_un local, remote;
  char buf[128];
  if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    cout << "Error with socket" << endl;
    return -1;
  }
  local.sun_family = AF_UNIX;
  strcopy(local.sun_path, SOCK_PATH);
  unlink(SOCK_PATH);
  len = strlen(local.sun_path) + size_of(local.sun_family);

  if (bind(s, (struct sockaddr *)&local, len) == -1) {
    cout << "Error with binding" << endl;
    return -1;
  }
  if (listen(s, 5) == -1) {
    cout << "Error with listening" << endl;
    return -1;
  }

  for (;;) {
    int done, n;
    t = sizeof(remote);
    if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
      cout << "Error with accepting " << endl;
      return -1;
    }
    done = 1;
    do {
      n = recv(s2, buf, 129, 0);
      if (n <= 0) {
        if (n < 0) {
          cout << "Error receiving" << endl;
        }
        done = 0;
      }
      if (done) {
        if (send(s2, buf. n, 0) < 0) {
          cout << "Error sending" << endl;
          done = 0;
        }
      }
    } while (done);
    close(s2);
  }
  return 0;
 }
