#include "game.h"

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

static int KEY = 1867821435;
static int k0 = 1236432234;
static int k1 = 1975087341;

static void sighandler(int signo){
    if (signo == SIGINT){
        int shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
        shmctl(shmd, IPC_RMID, 0);
        int p1 = shmget(k0, sizeof(int), IPC_CREAT | 0640);
        shmctl(p1, IPC_RMID, 0);
        int p2 = shmget(k1, sizeof(int), IPC_CREAT | 0640);
        shmctl(p2, IPC_RMID, 0);
        int playerWords = shmget(657396715, sizeof(int) * 2, IPC_CREAT | 0640);
        shmctl(playerWords, IPC_RMID, 0);
        int start = semget(1867821435, 1, IPC_CREAT | 0660);
        semctl(start, IPC_RMID, 0);
        printf("siginted\n");
        exit(0);
    }
}

int start(int KEY){
    int shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
    int *start;
    start = shmat(shmd, 0, 0);
    *start = 0;

    int* times[2];
    int player0 = shmget(k0, sizeof(int), IPC_CREAT | 0640);
    times[0] = shmat(player0, 0, 0);
    *times[0] = -1;

    int player1 = shmget(k1, sizeof(int), IPC_CREAT | 0640);
    times[1] = shmat(player1, 0, 0);
    *times[1] = -1;

    int playerWords = shmget(657396715, sizeof(int) * 2, IPC_CREAT | 0640);
    int* word = calloc(2, sizeof(int));
    word = shmat(playerWords, 0, 0);

    int semd = semget(KEY, 1, IPC_CREAT | 0660);
    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, 2);
    char* buffer;
    while (1){
        usleep(500000);
        buffer = typed();
        signal(SIGINT, sighandler);
        if (strcmp(buffer, "start") == 0){
            *start = 1;
        }
        //printf("times[0] is %d\ntimes[1] is %d\n", *times[0], *times[1]);
        if (*times[0] != -1){
            printf("Player 0 has finished in %d seconds\n", *times[0]);
            *times[0] = -1;
        }
        if (*times[1] != -1){
            printf("Player 1 has finished in %d seconds\n", *times[1]);
            *times[1] = -1;
        }
    }
}

int main(){
    int KEY = 1867821435;
    start(KEY);
}
