# Shared Memory IPC Project

## Copyright 2019 Justin Baum

## Installation

```
COMPILER=g++
$COMPILER -Wall -std=c++11 -pthreads -c project2-new.cc
$COMPILER -Wall -std=c++11 -o project2-new project2-new.o
```

or

```
make project2-new
```

On Linux

```
make project2-new-linux
```

## Usage

```
./project2-new file keyword
```

## Output

Currently it just reads the file into shared memory and reads out from the child. I had trouble getting shared memory into the threads, so even though there are threads and commented out code, they don't work.

## Timer

```
~/USC/CSCE311/project1 $ time (./project2-new anna.txt Anna &> /dev/null)

real    0m0.168s
user    0m0.130s
sys     0m0.007s
```
