#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int game(){
  time_t  begin = time(0);
  for (int i = 0; i < 1; i++){
    printf("Blue\n");
    char typed[10];
    fgets(typed, 5, stdin);
    while (strcmp(typed, "Blue") != 0
      fgets(typed, 5, stdin);
    }
  }
  time_t end = time(0);
  printf("Congratulations! You finished in %ld seconds\n", end - begin);
  return end - begin;
}
int main(){
  game();
}
