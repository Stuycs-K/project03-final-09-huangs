#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "game.c"

int connect(int KEY){
  //Semaphore stuff
  struct sembuf buffer;
  buffer.sem_num = 0;
  buffer.sem_flg = SEM_UNDO;
  buffer.sem_op = -1;
  int semd = semget(KEY, 1, 0644);
  int spotsleft = semctl(semd, 0, GETVAL);
  //Shared memory segments stuff
  int *data;
  int shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
  data = shmat(shmd, 0, 0);

  if (spotsleft == 0){
    printf("Waiting for a player to quit...\n");
  }
  int player;
  int* time;
  if (spotsleft == 1){
    int pkey = 1236432234;
    player = shmget(pkey, sizeof(int), IPC_CREAT | 0640);
    time = shmat(player, 0, 0);
  }
  if (spotsleft == 2){
    int pkey = 1975087341;
    player = shmget(pkey, sizeof(int), IPC_CREAT | 0640);
    time = shmat(player, 0, 0);
  }
  semop(semd, &buffer, 1);
  char bufferr[100];
  while (*data == 0){
    usleep(100000);
  }
  *time = game();
  return 0;
}
int main(){
    int KEY = 1867821435;
    connect(KEY);
}
