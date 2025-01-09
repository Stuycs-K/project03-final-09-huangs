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

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

int start(int KEY){
    int semd = semget(KEY, 1, IPC_CREAT | 0660);
    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, 2);
}

int main(){
    int KEY = 1867821435;
    start(KEY);
}