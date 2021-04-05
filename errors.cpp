//Name: Donovan McDonough
//date: 4/4/2021

#include "sharedmemory.h"
#include "errors.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <sys.types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

using namespace std;

string pPrefix;
string prefix;

void setup(const char* arg) {
   prefix = arg;
   pPrefix = arg;
   prefix += ": Error";
}

void perrorquit() {
   perror(prefix.c_tr());
   cleanup();
   exit(1);
}

void help(const char* error) {
   cerr << prefix << ": " << error << endl;
   cerr << "Use ' " << rawprefix;
   cerr << " -h for help" << endl;
   cleanup();
   exit(1);
}
