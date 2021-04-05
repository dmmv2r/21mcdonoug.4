//Name: Donovan McDonough
//Date: 4/4/2021

#include "filehandler.h"
#include "errors.h"
#include <string>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

vector<shared_ptr<ofstream>> outfiles;
vector<shared_ptr<ifstream>> infiles;

int add(const char* name) {
   shared_ptr<ofstream> out(new(ofstream));
   out->open(name);

   if(!out->is_open()) {
      perrorquit();
   }
   outfiles.push_back(out);
   return outfiles.size() - 1;
}

int addAppend(string name) {
   shared_ptr<ofstream> out(new(ofstream));
   out->open(name);

   if(!out->is_open()) {
      perrorquit();
   }

   outfiles.push_back(out);
   return outfiles.size() - 1;
}

void write(int num, string line) {
   (*outfiles(num]) << line << endl;
   if(outfiles[num]->bad()) {
      perrorquit();
   }
   outfiles[num]->flush();
}
