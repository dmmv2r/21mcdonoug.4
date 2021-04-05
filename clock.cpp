//Name: Donovan McDonough
//Date: 4/4/2021

#include "clock.h"
#include <ctime>

using namespace std;

float clock::toFloat() {
   return (float) this->sec + (float)this->nanoSec / (float)1e9;
}

string clock::toString() {
   int padding = 9 - to_string(this->nanoSec).size();
   string rep = to_string(this->sec) + ".";

   while(padding--) {
      rep += "0";
   }
   return rep + to_string(this->nanoSec);
}

void clock::add(long nano) {
   this->nanoSec += nano;
   while(this->nanoSec > 1e9) {
      this->nanoSec -= 1e9;
      this->sec += 1;
   }
}

