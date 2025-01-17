#include "game.h"

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

  int numPlayer = -1;
  if (spotsleft == 0){
    printf("Waiting for a player to quit...\n");
  }

  int player;
  long* time;
  int pkey;
  if (spotsleft == 1){
    pkey = 1236432234;
    numPlayer = 1;
  }
  if (spotsleft == 2){
    pkey = 1975087341;
    numPlayer = 0;
  }
  player = shmget(pkey, sizeof(long), IPC_CREAT | 0640);
  time = shmat(player, 0, 0);

  int namePlayers = shmget(256773432, sizeof(char *) * 2, IPC_CREAT | 0640);
  char** names;
  names = shmat(namePlayers, 0, 0);

  semop(semd, &buffer, 1);

  int flags = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, flags | O_NONBLOCK);
  char* bufferr;

  while (1){
    while (*data == 0){
      bufferr = typed();
      if (strcmp(bufferr, "setusername") == 0){
        printf("Change your username to:\n");
        names[numPlayer] = typed();
        printf("%d", *data);
        printf("Your username is now: %s.\n", names[numPlayer]);
      }
      free(bufferr);
    }
    game(numPlayer);
    printf("Waiting for the other player to finish or host to start...\n");
  }
  return 0;
}
int main(){
    int KEY = 1867821435;
    connect(KEY);
}
