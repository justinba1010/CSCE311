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

#define linelength = 1024

using namespace std;

void f(sem_t *sem, sem_t *sema, key_t *key, int shmid) {
  char *str = (char*)shmat(shmid, (void*)0, 1024);
  do {
    sem_wait(sema);
    cout << str << endl;
    usleep(2000);
    sem_post(sem);
  } while (str[0] != 0);
}

int main(int argc, char* argv[]) {
  sem_t *sem1, *sem2, *sem3, *sem4, *sem1a, *sem2a, *sem3a, *sem4a;
  sem1 = sem_open("sem1", O_CREAT, 0644, 0);
  sem2 = sem_open("sem2", O_CREAT, 0644, 0);
  sem3 = sem_open("sem3", O_CREAT, 0644, 0);
  sem4 = sem_open("sem4", O_CREAT, 0644, 0);
  sem_post(sem1);
  sem_post(sem2);
  sem_post(sem3);
  sem_post(sem4);
  sem1a = sem_open("sem1a", O_CREAT, 0644, 0);
  sem2a = sem_open("sem2a", O_CREAT, 0644, 0);
  sem3a = sem_open("sem3a", O_CREAT, 0644, 0);
  sem4a = sem_open("sem4a", O_CREAT, 0644, 0);
  key_t key1 = ftok("sharedmemoryfile1", 65);
  key_t key2 = ftok("sharedmemoryfile2", 64);
  key_t key3 = ftok("sharedmemoryfile3", 63);
  key_t key4 = ftok("sharedmemoryfile4", 62);
  int shmid1 = shmget(key1, 1024, 0666 | IPC_CREAT);
  int shmid2 = shmget(key2, 1024, 0666 | IPC_CREAT);
  int shmid3 = shmget(key3, 1024, 0666 | IPC_CREAT);
  int shmid4 = shmget(key4, 1024, 0666 | IPC_CREAT);

  if (!fork()) { /* Child */
    //int x = sem_getvalue(&sem1, &val);
    // Spawn 4 threads
    thread t1(f, sem1, sem1a, &key1, shmid1);
    thread t2(f, sem2, sem2a, &key2, shmid2);
    thread t3(f, sem3, sem3a, &key3, shmid3);
    thread t4(f, sem4, sem4a, &key4, shmid4);
    // Wait for 4 threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
  } else { /* PArent */
    string aline;
    ifstream myFile;
    myFile.open(argv[1]);
    int i = 0;
    sem_t* semaphores[4] = {sem1, sem2, sem3, sem4};
    sem_t* semaphoresa[4] = {sem1a, sem2a, sem3a, sem4a};
    //int shmids[4] = {shmid1, shmid2, shmid3, shmid4};
    char* sharedmemory[4] = {(char*)shmat(shmid1, NULL, 1024), (char*)shmat(shmid2, NULL, 1024), (char*)shmat(shmid3, NULL, 1024), (char*)shmat(shmid4, NULL, 1024)};
    if (myFile.is_open()) {
      while (getline(myFile, aline)) {
        //cout << aline << endl;
        memset(sharedmemory[i], (char)0, 1024);
        sem_wait(semaphores[i]);
        memcpy(sharedmemory[i], aline.c_str(), aline.length());
        usleep(2000);
        sem_post(semaphoresa[i]);
        i++;
        i %= 4;
      }
      // Signal to end
      for (i = 0; i < 4; ++i) {
        sem_wait(semaphores[i]);
        memset(sharedmemory[i], (char)0, 1024);
        usleep(2000);
        sem_post(semaphores[i]);
      }
    }
    wait(NULL);
    cout << "Finished" << endl;
  }
} // main
