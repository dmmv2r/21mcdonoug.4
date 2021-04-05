//Name:Donovan McDonough
//Date: 4/4/2021

#include <iostream>

using namespace std;

void findWaitTime(int processes[], int n, int bt[], int wt[], int quantum) {

   int rem_bt[n];

   for (int i = 0; i < n; i++) {
      rem_bt[i] = bt[i];
   }

   int t = 0;

   while(1) {
      bool done = true;

      for(int i = 0; i < n; i++) {
         if(rem_bt[i] > 0) {
            done = false;

            if(rem_bt[i] > quantum) {
               t += quantum;
               rem_bt[i] -= quantum;
            } else {
               t += rem_bt[i];
               wt[i] = t - bt[i];
               rem_bt[i] = 0;
            }
         }
      }

      if(done = true) {
         break;
      }
   }
}

void findTurnTime(int processes[], int n, int bt[], int wt[], int tat[]) {

   for(int i = 0; i < n; i++) {
      tat[i] = bt[i] + wt[i];
   }
}

void findAvgTime(int processes[], int n, int bt[], int quantum) {

   int wt[n];
   int tat[n];
   int total_wt = 0;
   int total_tat = 0;

   findWaitTime(processes, n, bt, wt, quantum);

   findTurnTime(processes, n, bt, wt, tat);

   cout << "Processes " << " Burst time " << " Waiting time " << " Turn around time" << endl;

   for(int i = 0; i < n; i++) {
      total_wt += wt[i];
      total_tat += tat[i];
      cout << " " << i + 1 << "\t\t" << bt[i] << "\t " << wt[i] << "\t\t " << tat[i] << endl;
   }

   cout << "Average wait time = " << (float)total_wt / (float)n << endl;;
   cout << "Average turn around time = " << (float)total_tat / (float)n << endl;

}

