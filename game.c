#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
char** randomWords(){
  int file = open("/dev/urandom", O_RDONLY, 0666);
  char ** words = malloc(sizeof(char*) * 10);
  int ints[10];
  for (int i = 0; i < 10; i++){
    int random;
    read(file, &random, sizeof(int));
    random = abs(random) % 100;
    int current = 0;
    //printf("%d\n", random);
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
  for (int i = 0; i < 10; i++){
    printf("ints[%d] is %d\n", i, ints[i]);
  }
  for (int i = 0; i < 100; i++){
    if (j < 10){
      words[j] = strsep(&wordchars, " ");
      if (i == ints[j]){
        printf("ints[j] is %d\n", ints[j]);
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
    printf("Type this (%d/10): length is %ld\n%s\n", i + 1, strlen(words[i]), words[i]);
    char typed[15];
    fgets(typed, 15, stdin);
    //printf("%s\n", typed);
    if (typed[strlen(typed) - 1] == '\n'){
      typed[strlen(typed) - 1] = '\0';
    }
    //printf("typed: %s\n", typed);
    //printf("strcmp(typed, words[i]) is %d\n", strcmp(typed, words[i]));
    while (strcmp(typed, words[i]) != 0){
      printf("You typed it wrong. Try again\n");
      fgets(typed, 15, stdin);
      if (typed[strlen(typed) - 1] == '\n'){
      typed[strlen(typed) - 1] = '\0';
      }
      //printf("%ld and %ld\n", strlen(words[i]), strlen(typed));
    }
  }
  time_t end = time(0);
  printf("Congratulations! You finished in %ld seconds\n", end - begin);
  return end - begin;
}
int main(){
  game();
}
