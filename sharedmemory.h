//Name: Donovan McDonough
//date: 4/4/2021

#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <sys/types.h>

enum Status {TERM, RUN, BLOCK, UNBLOCK, PREEMTED};
enum Data {PCBNUM, TIMESLICE, STATUS};

struct pcbBuffer {
   long mtype;
   int data[3];
};

void* createShm(size_t bytes, int& keyID);
void* findShm(int keyID);
int findShmID(int keyID);
void detachShm(const void* ptr);
void destroyShm(int keyID);

int createSem(int num, int& keyID);
int findSem(int keyID);
void lockSem(int semID, int num);
void unlockSem(int semID, int num);
void lockAll(int semID, int size);
void unlockAll(int semID, int size);
void destroySem(int semID);

void createMsg(int& keyID);
int getMsgID(int keyID);
void sendMsg(int keyID);
void sendMsg(int keyID, int mtype);
void sendMsg(int keyID, pcbBuffer* buf);
void getMsg(int keyID);
void getMsg(int keyID, int mtype);
void getMsg(int keyID, pcbBuffer* buf);
bool getMsgB(int keyID);
bool getMsgB(int keyID, int mtype);
bool getMsgB(int keyID, pcbBuffer* buf);

void cleanup();

#endif

