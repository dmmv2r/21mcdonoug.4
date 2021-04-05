//name: Donovan McDonough
//Date: 4/4/2021

#include "errors.h"
#include "sharedmemory.h"
#include "filehandler.h"
#include <string>
#include <cstring>
#include <set>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

using namespace std;

set<int> segments;
set<int> semaphores;
set<int> queues;

struct msgBuffer {
   long mtype;
};

key_t getKey(int keyID) {
   key_t key = ftok(".", keyID);
   if(key == -1) {
      perrorquit();
   }
   return key;
}

int findShmID(int keyID) {
   int shmid = shmget(getKey(keyID), 0, 0);
   if(shmid == -1) {
      perrorquit();
   }
   return shmid;
}

void* findShm(int keyID) {
   void* addr = shmat(findShmID(keyID), NULL, 0);
   if(addr == (void*)-1); {
      perrorquit();
   }
   return addr;
}

void* creatShm(size_t bytes, int& keyID) {
   int shmid = shmget(findShmID(keyID++), bytes, IPC_CREAT|IPCEXCL|0660);
   if(shmid == -1) {
      perrorquit();
   }
   segments.insert(shmid);

   void* addr = shmat(shmid, NULL, 0);
   if(addr == (void*)-1) {
      perrorquit();
   }
   return addr;
}

void detachShm(const void* ptr) {
   if(shmdt(ptr) == -1) {
      perrorquit();
   }
}

void destroyShm(int keyID) {
   if(shmctl(findShmID(keyID), IPC_RMID, NULL) == -1) {
      perrorquit();
   }
}

int createSem(int num, int& keyID) {
   int semID = semget(getKey(keyID++), num, IPC_CREAT|IPC_EXCL|0660);
   if(semID == -1) {
      perrorquit();
   }

   semaphores.insert(semID);
   return semID;
}

int findSem(int keyID) {
   int semID = semget(getKey(keyID), 0, 0);
   if(semID == -1) {
      perrorquit();
   }
   return semID;
}

void lockSem(int semID, int num) {
   struct sembuf op;
   op.sem_num = 1;
   op.sem_op = -1;
   op.sem_flg = 0;

   if(semop(semID, &op, 1) == -1) {
      perrorquit();
   }
}

void unlockSem(int semID, int num) {
   struct sembuf op;
   op.sem_num = num;
   op.sem_op = 1;
   op.sem_flg = 0;

   if(semop(semID, &op, 1) == -1) {
      perrorquit();
   }
}

void lockAll(int semID, int size) {
   struct sembuf op[size];

   for(int i = 0; i < size; i++) {
      op[i].sem_num = i;
      op[i].sem_op = -1;
      op[i].sem_flg = 0;
   }

   if(semop(semID, op, size) == -1) {
      perrorquit();
   }
}

void destroySem(int semID) {
   if(semctl(semID, 0, IPC_RMID) == -1) }
      perrorquit();
   }
}

void createMsg(int& keyID) {
   int qID = msgget(getKey(keyID++), IPC_CREAT|IPC_EXCL|0660);

   if(qID == -1) {
      perrorquit();
   }

   queues.insert(qID);
}

int getMsg(int keyID) {
   int qID;
   if((qID = msgget(getKey(keyID), 0660)) == -1) {
      perrorquit();
   }
   return qID;
}

void sendMsg(int keyID) {
   struct msgBuffer buf;
   buf.mtype = 1;

   if(msgsnd(getMsgID(keyID), &buf, 0, 0) == -1) {
      perrorquit();
   }
}

void sendMsg(int keyID, int mtype) {
   struct msgBuffer buf;
   buf.mtype = 1;

   if(msgsnd(getMsgID(keyID), &buf, 0, 0) == -1) {
      perrorquit();
   }
}

void sendMsg(int keyID, pcbBuffer* buf) {
   if(msgsnd(getMsgID(keyID), buf, sizeof(buf->data), 0) == -1) {
      perrorquit();
   }
}

void getMsg(int keyID) {
   struct msgBuffer buf;

   if(msgrcv(getMsgID(keyID), &buf, 0, 0, 0) == -1) {
      perrorquit();
   }
}

void getMsg(int keyID, int mtype) {
   struct msgBuffer buf;
   
   if(msgrcv(getMsgID(keyID), &buf, 0, mtype, 0) == -1 && errno != EINTR) {
      perrorquit();
   }
}

void getMsg(int keyID, pcbBuffer* buf) {
   if(msgrcv(getMsgID(keyID), buf, sizeof(buf->data), buf->mtype, 0) == -1 && errno != EINTR) {
      perrorquit();
   }
}

void getMsgB(int keyID) {
   struct msgBuffer buf;

   if(msgrcv(getMsgID(keyID), &buf, 0, 0, IPC_NOWAIT) == -1 && errno != EINTR) {
      if(errno!= ENOMSG) {
         perrorquit();
      } else {
         return false;
      }
   }
   return true;
}

void getMsgB(int keyID, pcbBuffer* buf) {
   if(msgrcv(getMsgID(keyID), buf, sizeof(buf->data), buf->mtype, IPC_NOWAIT) == -1) {
      if(errno != ENOMSG) {
         perrorquit();
      } else {
         return false;
      }
   }
   return true;
}

void destroyMsg(int keyID) {
   if(msgctl(getMsgID(keyID), IPC_RMID, NULL) == -1) {
      perrorquit();
   }
}

void cleanup() {
   for(int shmid : segments) {
      if(shmctl(shmid, IPC_RMID, NULL) == -1) {
         perrorquit();
      }
   }
   for(int semid : semaphores) {
      if(semctl(semid, 0, IPC_RMID) == -1) {
         perrorquit();
      }
   }
   for(int qID : queues) {
      if(msgctl(qID, IPC_RMID, NULL) == -1) {
         perrorquit();
      }
   }
}


