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

int connect(int KEY){
  struct sembuf buffer;
  buffer.sem_num = 0;
  buffer.sem_flg = SEM_UNDO;
  buffer.sem_op = -1;
  int semd = semget(KEY, 1, 0644);
  printf("Waiting for a player to quit...\n");
  semop(semd, &buffer, 1);
  char bufferr[100];
  printf("test\n");
  fgets(bufferr, 100, stdin);
  return 0;
}
int main(){
    int KEY = 1867821435;
    connect(KEY);
}