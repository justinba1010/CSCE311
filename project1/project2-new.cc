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

bool checkStringForKeyword(string *line, string *keyword);

void fthread(int start, int end, char *sharedmemory, char *keyword) {
  string *s;
  memcpy(s, sharedmemory, end-start);
  if (!checkStringForKeyword(s, keyword)) {
    memset(sharedmemory+start, 2, end-start);
  }
}

bool checkStringForKeyword(char *line2, char *keyword2) {
  string line;
  string keyword;
  strcpy(line, line2);
  strcpy(keyword, keyword2);
  int pos = line.find(keyword);
  //cout << pos << endl;
  if (pos < 0) return false;
  if (pos == 0 && !isalpha(line.at(pos + keyword.length())))
    return true;
  if (pos == 0) return false;
  if (!isalpha(line.at(pos-1)) && !isalpha(line.at(pos + keyword.length())))
    return true;
  return false;
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
    char *keyword = argv[2];
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
      thread t1(fthread, start, end, sharedmemory, keyword);
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
    vector<string> sorty;
    char *x = sharedmemory;
    int length = 0;
    while (*x != 0) {
      char* stringy;
      if (*x == 1) { //New line
        char stringycpy[length];
        for(int i = (x-sharedmemory)-length; i < length; i++) {
          stringycpy[i] = *(x-length+i);
        }
        strcpy(stringy, stringycpy);
        length = 0;
      }
      if (*x == 2) {
        length = 0;
      }
      x++;
    }
    shmctl(shmid1, IPC_RMID, NULL);
  }
}
