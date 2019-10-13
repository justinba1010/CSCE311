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
#define SIZE 2024000

using namespace std;

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
      cout << x;
      i++;
      x = sharedmemory[i];
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
