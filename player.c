#include "game.h"

void setUsername(int numPlayer, char* name){
  if (numPlayer == 0){
    printf("Your current username is %s. Change your username to:\n", name);
  }
  else{
    printf("Your current username is %s. Change your username to:\n", &name[15]);    
  }
  char* newName = typed();
  int smaller = strlen(newName);
  if (15 < smaller){
    smaller = 15;
  }
  if (numPlayer == 0){
    for (int i = 0; i < smaller; i++){
      name[i] = newName[i];
    }
    for (int i = smaller; i < 15; i++){
      name[i] = '\0';
    }
  }
  else{
    for (int i = 0; i < smaller; i++){
      name[i + 15] = newName[i];
    }
    for (int i = smaller; i < 30; i++){
      name[i + 15] = '\0';
    }
  }
  if (numPlayer == 0){
    printf("Your username is now %s.\n", name);
  }
  else{
    printf("Your username is now %s.\n", &name[15]);    
  }
}
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
  printf("You are now playing Budget Typeracer.\n");
  int player;
  int* time;
  int pkey;
  if (spotsleft == 1){
    pkey = 1236432234;
    numPlayer = 1;
  }
  if (spotsleft == 2){
    pkey = 1975087341;
    numPlayer = 0;
  }
  player = shmget(pkey, sizeof(int), IPC_CREAT | 0640);
  time = shmat(player, 0, 0);
  *time = 100;
  int playerNames = shmget(256773432, sizeof(char) * 30, IPC_CREAT | 0666);
  char* name = shmat(playerNames, 0, 0);

  semop(semd, &buffer, 1);

  int flags = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, flags | O_NONBLOCK);
  char* bufferr;

  while (1){
    while (*data == 0){
      bufferr = typed();
      if (strcmp(bufferr, "setusername") == 0){
        setUsername(numPlayer, name);
      }
      if (strlen(bufferr) != 0){
        free(bufferr);
      }
    }
    *time = game(numPlayer);
    printf("*time is %d\n", *time);
    printf("Waiting for the other player to finish or host to start...\n");
  }
  return 0;
}
int main(){
    int KEY = 1867821435;
    connect(KEY);
}
