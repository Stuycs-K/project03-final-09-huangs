#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

char** randomWords(){
  int file = open("/dev/urandom", O_RDONLY, 0666);
  char ** words = malloc(sizeof(char*) * 10);
  int * ints = malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++){
    int random;
    read(file, &random, sizeof(int));
    random = abs(random) % 100;
    int current = 0;
    printf("%d\n", random);
    while (current != i && ints[current] < random){
      current++;

    }
    for (int j = 1; j < i; j++){
      ints[current + j] == ints[current + j - 1];
    }
    ints[current] = random;
  }
  close(file);
  printf("\n");
  for (int i = 0; i < 10; i++){
    printf("%d\n", ints[i]);
  }
}

int game(){
  time_t  begin = time(0);
  for (int i = 0; i < 10; i++){
    printf("Blue\n");
    char typed[10];
    fgets(typed, 5, stdin);
    while (strcmp(typed, "Blue") != 0){
      fgets(typed, 5, stdin);
      system("clear");
      printf("You typed it wrong. Try again\n");
    }
  }
  time_t end = time(0);
  printf("Congratulations! You finished in %ld seconds\n", end - begin);
  return end - begin;
}
int main(){
  randomWords();
  //game();
}
