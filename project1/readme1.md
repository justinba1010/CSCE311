# Server Pipe IPC Project

## Copyright 2019 Justin Baum

## Installation

```
COMPILER=g++
$COMPILER -Wall -std=c++11 -c project.cc
$COMPILER -Wall -std=c++11 -o project project.o
```

## Usage

```
./project file keyword
```

## Output

It will output each line in the file that contains the keyword in ASCII encoding. I did not have enough time to write the alphabeticalization.

## Notes

## Explanation

I used a 1 character buffer to pass inbetween the server and client, and using the built in blocking by `read` and `write` with unix domain sockets, I enforce order of reading in and out of the socket. This is a much slower version of passing to the pipe. I went with it, as I would either need to pass a fixed size char array into the pipe and do the logic on the child side, but I thought it would be easier to do with 1 character at a time.

## Timer

On OS X

```
[/Users/justinbaum/USC/CSCE311/project1] (master)
~/USC/CSCE311/project1 $ time (./project anna.txt Anna &> /dev/null)

real    0m2.845s
user    0m1.010s
sys     0m4.333s
```

On Ubuntu/AMD64(School Servers)

```
[/Users/justinbaum]
~ $ ssh -p 222 jabaum@$USC
******************************************************************************
*                                                                            *
* This system is for the use of authorized users only.  Usage of this system *
* may be monitored and recorded by system personnel.                         *
*                                                                            *
* Anyone using this system expressly consents to such monitoring and is      *
* advised that if such monitoring reveals possible evidence of criminal      *
* activity, system personnel may provide the evidence from such monitoring   *
* to law enforcement officials.                                              *
*                                                                            *
******************************************************************************
Password:
Password:
Duo two-factor login for jabaum

Enter a passcode or select one of the following options:

 1. Duo Push to XXX-XXX-3040
 2. Phone call to XXX-XXX-3040
 3. SMS passcodes to XXX-XXX-3040

Passcode or option (1-3): 1

Pushed a login request to your device...
Success. Logging you in...
jabaum [~]$ cd CSCE311/
jabaum [~/CSCE311]$ ls
project1  semaphore.c  semaphore.cc
jabaum [~/CSCE311]$ cd project1/
jabaum [~/CSCE311/project1]$ make project
g++ -Wall -std=c++11 -o project project.o
project.o: file not recognized: File format not recognized
collect2: error: ld returned 1 exit status
makefile:22: recipe for target 'project' failed
make: *** [project] Error 1
jabaum [~/CSCE311/project1]$ rm project.o
jabaum [~/CSCE311/project1]$ make project
g++ -Wall -std=c++11 -c project.cc
g++ -Wall -std=c++11 -o project project.o
jabaum [~/CSCE311/project1]$ ./project project.cc 
jabaum [~/CSCE311/project1]$ ./project project.cc keyword
bool checkStringForKeyword(string *line, string *keyword) {

  int pos = line->find(*keyword);

  if (pos == 0 && !isalpha(line->at(pos + keyword->length())))

  if (!isalpha(line->at(pos-1)) && !isalpha(line->at(pos + keyword->length())))

        string keyword(argv[2]);

            if (checkStringForKeyword(&line, &keyword)) lines.push_back(line);

jabaum [~/CSCE311/project1]$ timer (./project anna.txt Anna &> /dev/null)
-bash: syntax error near unexpected token `./project'
jabaum [~/CSCE311/project1]$ time (./project anna.txt Anna &> /dev/null)

real	0m1.227s
user	0m0.417s
sys	0m2.028s
jabaum [~/CSCE311/project1]$ 
```
