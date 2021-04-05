//Name: Donovan McDonough
//Date: 4/4/2021

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
   int opt;
   int seconds;
   string logfile;

   seconds = 100;
   logfile = "logfile";

   while((opt = getopt(argc, argv, "hs:l:")) != -1) {
      switch(opt) {
         case 'h':
            cout << "Usage..." << endl;
            return -1;
         case 's':
            seconds = atoi(optarg);
            break;
         case 'l':
            logfile = optarg;
            break;
         default:
            cout << "invalid inputs" << endl;
            return -1;
      }
   }

   cout << "seconds = " << seconds << endl;
   cout << "logfile = " << logfile << endl;

   cout << "leaving OSS" << endl;
   return 0;
}
