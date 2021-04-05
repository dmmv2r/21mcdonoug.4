//Name: Donovan McDonough
//date: 4/4/2021

#include "errors.h"
#include "sharedmemory.h"
#include "scheduler.h"
#include "clock.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <csignal>
#include <vector>

volatile bool earlyQuit = false;

void signalHandler(int sigNum) {
   exit(-1);
}

int main(int argc, char* argv[]) {
   signal(SIGINT, signalHandler);
   setup(argv[0]);
   srand(getpid());

   return 0;
}
