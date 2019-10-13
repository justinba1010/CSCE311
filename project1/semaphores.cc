#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <locale>
#include <string>
#include <thread>
#include <semaphore.h>

using namespace std;

int main(int argc, char* argv[]) {
  sem_t sem1;
  sem_init(&sem1, 1, 0);
  if(!fork()) {
    sem_wait(&sem1);
    cout << "Hello World 2" << endl;
  } else {
    sleep(5);
    cout << "Hello World 1" << endl;
    sem_post(&sem1);
    wait(NULL);
  }
  return 0;
}
