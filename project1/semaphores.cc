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
#include <fstream>
#include <iostream>
#include <semaphore.h>
#include <stdio.h>
#include <string>
#include <sysexits.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char* argv[]) {
  //sem_t *sem1 = (sem_t*)mmap(0, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, 0, 0 );
  //sem_init(sem1, 0, 0);
  sem_t *sem1;
  sem_t *sem2;
  sem1 = sem_open("my semaphore", O_CREAT, 0644, 0);
  sem2 = sem_open("my semaphore1", O_CREAT, 0644, 1);
  if(!fork()) {
    sem_wait(sem1);
    //while(1) {
      //int *p = new int(0);
      //int x = sem_getvalue(sem1, p);
      //if (*p == 1) break;
      //cout << *p << endl;
      //cout << x << endl;
      //sleep(1);
    //}
    sleep(1);
    cout << "Hello World 2" << endl;
    cout << "Hello World 3" << endl;
    sem_post(sem2);
  } else {
    sleep(1);
    cout << "Hello World 1" << endl;
    sem_wait(sem2);
    sem_post(sem1);
    sem_wait(sem2);
    cout << "Hello World 4" << endl;
    wait(NULL);
  }
  return 0;
}
