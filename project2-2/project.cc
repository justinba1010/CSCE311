#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <locale>
#include <string>
#include <sys/wait.h>
#include <algorithm>

using namespace std;

void getChar(ifstream *file, char *buf) {
  *file >> *buf;
  //cout << *buf;
}

void readChar(char *buf) {
  //cout << *buf;
}
using namespace std;
bool checkStringForKeyword(string *line, string *keyword) {
  int pos = line->find(*keyword);
  //cout << pos << endl;
  if (pos < 0) return false;
  if (pos == 0 && !isalpha(line->at(pos + keyword->length())))
    return true;
  if (pos == 0) return false;
  if (!isalpha(line->at(pos-1)) && !isalpha(line->at(pos + keyword->length())))
    return true;
  return false;
}

int main(int argc, char* argv[])
{
    int sv[2]; /* the pair of socket descriptors */
    char buf = 127; /* for data exchange between processes */
    char zero = 0;
    char one = 1;
    char newLine = '\n';

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        exit(1);
    }

    if (argc != 3) {
      exit(1);
    }
    if (!fork()) {  /* child */
        string keyword(argv[2]);
        vector<string> lines;
        string line = "";
        while(buf) {
          read(sv[1], &buf, 1);
          line.append(&buf, 1);
          if (buf == 1) {
            readChar(&newLine);
            if (checkStringForKeyword(&line, &keyword)) lines.push_back(line);
            line = "";
          } else {
            readChar(&buf);
          }
        }
        for(auto it = lines.begin(); it != lines.end(); ++it) {
          for (char x : *it) {
            write(sv[1], &x, 1);
          }
          write(sv[1], &one, 1);
        }
        write(sv[1], &zero, 1);
    } else { /* parent */
      string aline;
      ifstream myFile;
        myFile.open(argv[1]);
        if (myFile.is_open()) {
          while(getline(myFile, aline)) {
              for(long unsigned int i = 0; i < aline.length(); ++i) {
                buf = aline.at(i);
                write(sv[0], &buf, 1); // CHAR
              }
              write(sv[0], &one, 1); //New Line
          }
          write(sv[0], &zero, 1); // EOF
        } else {
          cout << "Error opening file" << endl;
          exit(1);
        }
        vector<string> sorty;
        string stringy;
        do {
          read(sv[0], &buf, 1);
          if(buf == 1) {
            sorty.push_back(stringy);
            stringy = "";
          } else {
            stringy = stringy + buf;
          }
        } while (buf);
        sort(sorty.begin(), sorty.end());
        for(string s : sorty) {
          cout << s << endl;
        }
        wait(NULL); /* wait for child to die */
    }

    return 0;
}
