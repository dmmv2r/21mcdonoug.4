//Name: Donovan McDonough
//Date: 4/4/2021

#ifndef SCHEDULER_H
#define SCHEDULER_H

//geeksforgeeks.org/program-round-robin-scheduling-set-1/

void findWaitTime(int processes[], int n, int bt[], int wt[], int quantum);
void findTurnTime(int processes[], int n, int bt[], int wt[], int tat[]);
void findAvgTime(int processes[], int n, int bt[], int quantum);

#endif
