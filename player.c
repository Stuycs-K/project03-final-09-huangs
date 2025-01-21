#include "game.h"

int pkey;
static void sighandler(int signo){
  int player;
  int* time;
  int *data;
  int shmd = shmget(1867821435, sizeof(int), IPC_CREAT | 0640);
  data = shmat(shmd, 0, 0);
  int sem;
  int semd = semget(1867821435, 1, 0644);
  sem = semctl(semd, 0, GETVAL);
  if (signo == SIGINT){
    if (*data == -1000){
      printf("The host has quit the game.\n");
      if (sem == 1){
        shmctl(shmd, IPC_RMID, 0);
      }
      exit(0);
    }
    else{
      if (pkey == 1236432234){
        player = shmget(pkey, sizeof(int), IPC_CREAT | 0640);
        time = shmat(player, 0, 0);
        *time = -1000;
      }
      else{
        player = shmget(1975087341, sizeof(int), IPC_CREAT | 0640);
        time = shmat(player, 0, 0);
        *time = -1000;
      }
      printf("\nYou have left the game.\n");
      exit(0);
    }
  }
}
void setUsername(int numPlayer, char* name){
  printf("Your current username is %s. Change your username to:\n", &name[numPlayer * 15]);
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
  printf("Your username is now %s.\n", &name[numPlayer * 15]);
}
void checkScore(){
  int score = open("./score.txt", O_RDONLY | O_CREAT, 0666);
  char* buffer = calloc(50, sizeof(char));
  read(score, buffer, 50);
  if (strlen(buffer) == 0){
      printf("Score is currently empty.\n");
  }
  else{
      char* numbers = strstr(buffer, "verylongseparator") + 18;
      char* currentnumber = strsep(&numbers, "\n");
      char* currentname = strsep(&buffer, "\n");
      printf("The current head to head score between %s and %s is %s to %s.\n", currentname, strsep(&buffer, "\n"), currentnumber, numbers);
  }
  close(score);
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
  system("clear");
  printf("You are now playing Budget Typeracer.\n");
  int player;
  int* time;
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
  *time = -1;
  int playerNames = shmget(256773432, sizeof(char) * 30, IPC_CREAT | 0666);
  char* name = shmat(playerNames, 0, 0);
  char newName[100];
  sprintf(newName, "Player %d", numPlayer + 1);
  if (numPlayer == 0){
    for (int i = 0; i < strlen(newName); i++){
      name[i] = newName[i];
    }
    for (int i = strlen(newName); i < 15; i++){
      name[i] = '\0';
    }
  }
  else{
    for (int i = 0; i < strlen(newName); i++){
      name[i + 15] = newName[i];
    }
    for (int i = strlen(newName); i < 30; i++){
      name[i + 15] = '\0';
    }
  }
  semop(semd, &buffer, 1);

  int flags = fcntl(0, F_GETFL, 0);
  fcntl(0, F_SETFL, flags | O_NONBLOCK);
  char* bufferr;

  printf("Type \"setusername\" to change your username.\n");
  printf("Type \"score\" to check the score.\n");
  int ingame = 1;
  while (*data == 1){
    if (*data == -1000){
      kill(getpid(), SIGINT);
    }
    if (ingame){
      printf("Waiting for the game to be over...\n");
      ingame = 0;
    }
  }
  while (1){
    usleep(1000000);
    if (*data == -1000){
      kill(getpid(), SIGINT);
    }
    signal(SIGINT, sighandler);
    while (*data == 0){
      bufferr = typed();
      if (*data == -1000){
        kill(getpid(), SIGINT);
      }
      if (strcmp(bufferr, "setusername") == 0){
        setUsername(numPlayer, name);
      }
      if (strcmp(bufferr, "score") == 0){
        checkScore();
      }
      if (strlen(bufferr) != 0){
        free(bufferr);
      }
    }
    *time = game(numPlayer);
    if (*time != 0){
      printf("Waiting for the host to start...\n");
    }
  }
  return 0;
}
int main(){
    int KEY = 1867821435;
    connect(KEY);
}
