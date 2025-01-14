#include "game.h"
char** randomWords(){
  int listsize = 1000;
  int file = open("/dev/urandom", O_RDONLY, 0666);
  char ** wordList = malloc(sizeof(char*) * 10);
  int ints[10];
  for (int i = 0; i < 10; i++){
    int random;
    read(file, &random, sizeof(int));
    random = abs(random) % listsize;
    int current = 0;
    while (current != i && ints[current] < random){
      current++;
    }
    for (int j = 0; j < i - current; j++){
      ints[i - j] = ints[i - j - 1];
    }
    ints[current] = random;
  }
  close(file);
  int wordlist = open("./words.txt", O_RDONLY, 0666);
  struct stat * stat_buffer;
  stat_buffer = malloc(sizeof(struct stat)*1);
  stat( "./words.txt", stat_buffer);
  char * wordchars = malloc((int)stat_buffer->st_size);
  read(wordlist, wordchars, (int)stat_buffer->st_size);
  int j = 0;
  for (int i = 0; i < listsize; i++){
    if (j < 10){
      wordList[j] = strsep(&wordchars, " ");
      if (i == ints[j]){
        j++;
      }
    }
  }
  free(stat_buffer);
  return wordList;
}
char * typed(){
  char * typed = malloc(15);
  while(read(0, typed, 15) == -1);
  if (typed[strlen(typed) - 1] == '\n'){
    typed[strlen(typed) - 1] = '\0';
  }
  return typed;
}
void generateString(int* word){
  system("clear");
  for (int i = 0; i < 2; i++){
    printf("Player %d ", i + 1);
    for (int j = 0; j < word[i] * 50 / 10; j++){
      printf("_");
    }
    printf("car");
    for (int j = word[i] * 50 / 10; j < 50; j++){
      printf("_");
    }
    printf("\n");
  }
  printf("player 1 is on %d\n", word[0]);
  printf("player 2 is on %d\n", word[1]);
}

long game(int numPlayer){
  int KEY = 657396715;
  int shmd = shmget(KEY, sizeof(int) * 2, IPC_CREAT | 0640);
  int* word = malloc(sizeof(int) * 2);
  word = shmat(shmd, 0, 0);
  word[0] = 0;
  word[1] = 0;

  char** wordList = randomWords();
  time_t  begin = time(0);
  generateString(word);
  for (int i = 0; i < 10; i++){
    printf("Type this (%d/10):\n%s\n", i + 1, wordList[i]);
    char * input;
    input = typed();
    word[numPlayer]++;
    while (strcmp(input, wordList[i]) != 0){
      printf("You typed it wrong. Try again\n");
      input = typed();
    }
    generateString(word);
  }
  time_t end = time(0);

  printf("Congratulations! You finished in %ld seconds\n", end - begin);
  free(wordList);
  return 1;
}
