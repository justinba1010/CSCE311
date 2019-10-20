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
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
// 4 MB of RAM
#define SIZE 4194304

using namespace std;


void fthread(int start, int end, char *sharedmemory) {
  int x = start;
  while (x < end) {
    sharedmemory[x] += 3;
    ++x;
  }
}

int main(int argc, char* argv[]) {
  sem_t *sema;
  sema = sem_open("sema", O_CREAT, 0644, 0);
  key_t key1 = ftok("sharedmemoryfile1", 65);

  if(!fork()) { /* Child */
    sem_wait(sema);
    int shmid1 = shmget(key1, SIZE, 0666 | IPC_CREAT);
    cout << shmid1 << endl;
    char *sharedmemory = (char*)shmat(shmid1, (void*)0, SIZE);
    char x = sharedmemory[0];
    int i = 0;
    while (x != 0) {
      //cout << x;
      i++;
      x = sharedmemory[i];
    }
		x = sharedmemory[0];
    i = 0;
    int start = 0;
    int end = -1;
    while (x != 0) {
      while (x != 0 || x == '\n') {
        i++;
        x = sharedmemory[i];
      }
      thread t1(fthread, start, end, sharedmemory);
      t1.join();
      if (x != 0) {
        end = i;
        start = end + 1;
        i++;
      }
    }
    x = start; //remove warning when debugging
    char *e = sharedmemory;
    while (*e != '\0') {
      cout << *e;
      ++e;
    }
        
  } else { /* Parent */
    ifstream file(argv[1]);
    int shmid1 = shmget(key1, SIZE, 0666 | IPC_CREAT);
    cout << shmid1 << endl;
    char *sharedmemory = (char*)shmat(shmid1, (void*)0, SIZE);
    file.read(sharedmemory, SIZE);
    sem_post(sema);
    wait(NULL);
    shmctl(shmid1, IPC_RMID, NULL);
  }
}
