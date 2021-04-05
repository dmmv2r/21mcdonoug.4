//Name: Donovan McDonough
//4/4/2021

#ifndef CHILDHANDLER_H
#define CHILDHANDLER_H

#include <string>

using namespace std;

char** makeArg(string line, int& size);
void freeArg(char** arg, int size);
int forExec(string cmd, int& counter);
int forkExdc(const char* cmd, int& counter);
int updateCount(int& count);
int waitChild(int& count);
int waitPid(int pid, int& count);
void endall();

#endif
