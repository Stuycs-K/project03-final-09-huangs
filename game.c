#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int game(){
  time_t  begin = time(0);
  printf("%ld", begin);
  for (int i = 0; i < 1; i++){
    printf("Blue\n");
    char typed[10];
    fgets(typed, 5, stdin);
    while (strcmp(typed, "Blue") != 0){
      fgets(typed, 5, stdin);
    }
  }
  return begin;
}
int main(){
  game();
}
