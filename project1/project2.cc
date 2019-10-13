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

#define linelength = 1024

using namespace std;

void f(sem_t *sem, sem_t *sema, key_t *key) {
  do {
    sem_wait(sem);
    
  } while (false);
}

int main(int argc, char* argv[]) {
  sem_t sem1, sem2, sem3, sem4, sem1a, sem2a, sem3a, sem4a;
  sem_init(&sem1, 1, 1);
  sem_init(&sem2, 1, 1);
  sem_init(&sem3, 1, 1);
  sem_init(&sem4, 1, 1);
  sem_init(&sem1a, 1, 1);
  sem_init(&sem2a, 1, 1);
  sem_init(&sem3a, 1, 1);
  sem_init(&sem4a, 1, 1);
  key_t key1 = ftok("sharedmemoryfile1", 65);
  key_t key2 = ftok("sharedmemoryfile2", 65);
  key_t key3 = ftok("sharedmemoryfile3", 65);
  key_t key4 = ftok("sharedmemoryfile4", 65);

  if (!fork()) { /* Child */
    //int x = sem_getvalue(&sem1, &val);
    // Spawn 4 threads
    thread t1(f, &sem1, &sem1a, &key1);
    thread t2(f, &sem2, &sem2a, &key2);
    thread t3(f, &sem3, &sem3a, &key3);
    thread t4(f, &sem4, &sem4a, &key4);
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
    sem_t* semaphores[4] = {&sem1, &sem2, &sem3, &sem4};
    sem_t* semaphoresa[4] = {&sem1a, &sem2a, &sem3a, &sem4a};
    if (myFile.is_open()) {
      while (getline(myFile, aline)) {
        i++;
        i %= 4;
        sem_wait(semaphores[i]);
        sem_wait(semaphores[
      }
    }
        
    sem_post(&sem1);
    
    wait(NULL);
    cout << "Finished" << endl;
  }
} // main
