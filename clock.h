//Name: Donovan McDonough
//Date: 4/4/2021

#ifndef CLOCK_H
#define CLOCK_H

#include <stdlib.h>
#include<string>

using namespace std;

struct clock {
   long sec;
   long nanoSec;

   clock() {
      sec = 0;
      nanoSec = 0;
   }

   float toFloat();
   string toString();

   void add(long nano);
   void subtr(long nano);
   float nextrand(long max);
   void set(float time);
   void set(string time);
};

string logid();

#endif
