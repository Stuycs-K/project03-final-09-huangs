#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
char** randomWords(){
  int listsize = 1000;
  int file = open("/dev/urandom", O_RDONLY, 0666);
  char ** words = malloc(sizeof(char*) * 10);
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
      words[j] = strsep(&wordchars, " ");
      if (i == ints[j]){
        j++;
      }
    }
  }
  free(stat_buffer);
  return words;
}

int game(){
  char** words = randomWords();
  time_t  begin = time(0);
  for (int i = 0; i < 10; i++){
    printf("Type this (%d/10):\n%s\n", i + 1, words[i]);
    char typed[15];
    fgets(typed, 15, stdin);
    if (typed[strlen(typed) - 1] == '\n'){
      typed[strlen(typed) - 1] = '\0';
    }
    while (strcmp(typed, words[i]) != 0){
      printf("You typed it wrong. Try again\n");
      fgets(typed, 15, stdin);
      if (typed[strlen(typed) - 1] == '\n'){
      typed[strlen(typed) - 1] = '\0';
      }
    }
  }
  time_t end = time(0);
  printf("Congratulations! You finished in %ld seconds\n", end - begin);
  free(words);
  return end - begin;
}
int main(){
  game();
}
