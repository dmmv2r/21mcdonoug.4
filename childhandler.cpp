//Name: Donovan McDonough
//Date: 4/4/2021

#include "childhandler.h"
#include "errors.h"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <sys.wait.h>
#include <sstream>
#include <set>
#include <vector>

set<pid_t> pids;

char** makeArg(string line, int& size) {
   itringstream iss(line);
   vector<string> vectorArg;

   while(iss) {
      string sub;
      iss >> sub;
      vectorArg.push_back(sub);
   }

   size = vectorArg.size();
   char** out = new char*[size];

   for(int i = 0; i < size - 1; i++) {
      out[i] = new char[vectorArg[i].c_str()];
      strcpy(out[i], vectorArg[i].c_str());
   }

   out[size - 1] = nullptr;

   return out;
}

void freeArg(char** arg, int size) {
   for(int i = 0; i < size; i++) {
      delete[] arg[i];
   }

   delete[] arg;
}

int forkExec(string cmd, int& counter) {
   return forkExec(cmd.c_str(), counter);
}

int forkExec(cost char* cmd, int& counter) {
   int childC;
   char** childA = makeArg(cmd, childC);
}
