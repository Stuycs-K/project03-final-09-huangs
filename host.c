#include "game.h"

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

static int KEY = 1867821435;
static int k0 = 1975087341;
static int k1 = 1236432234;

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
        int playerNames = shmget(256773432, sizeof(char*) * 2, IPC_CREAT | 0640);
        shmctl(playerNames, IPC_RMID, 0);
        printf("siginted\n");
        exit(0);
    }
}
void checkScore(){
    int leaderboard = open("./leaderboard.txt", O_RDONLY | O_CREAT, 0666);
    char* buffer = calloc(50, sizeof(char));
    read(leaderboard, buffer, 50);
    if (strlen(buffer) == 0){
        printf("Leaderboard is empty.\n");
    }
    else{
        char* numbers = strstr(buffer, "verylongseparator") + 18;
        char* currentnumber;
        char* currentname;
        printf("The current head to head score between %s and %s is %s to %s.\n", strsep(&buffer, "\n"), strsep(&buffer, "\n"), strsep(&numbers, "\n"), strsep(&numbers, "\n"));
    }
}
void updateScore(char* p1, char* p2, int t1, int t2){
    int leaderboard = open("./leaderboard.txt", O_TRUNC | O_RDWR | O_CREAT, 0666);
    char* buffer = calloc(50, sizeof(char));
    read(leaderboard, buffer, 50);
    char* newbuffer = calloc(50, sizeof(char));
    if (strlen(buffer) == 0){
        sprintf(newbuffer, "%s\n%s\nverylongseparator\n%d\n%d", p1, p2, t1, t2);
        write(leaderboard, newbuffer, 50);
    }
    else{
        char* numbers = strstr(buffer, "verylongseparator") + 18;
        char* currentnumber;
        char* currentname;
        if (strcmp(strsep(&buffer, "\n"), p1) == 0 && strcmp(strsep(&buffer, "\n"), p2) == 0){
            char* firstscore = strsep(&numbers, "\n");
            int first = atoi(firstscore);
            int second = atoi(strsep(&numbers, "\n"));
            if (t1 >= t2){
                first++;
            }
            if (t1 <= t2){
                second++;
            }
            sprintf(newbuffer, "%s\n%s\nverylongseparator\n%d\n%d", p1, p2, first, second);
            write(leaderboard, newbuffer, 50);
        }
        else{
            int first = 0;
            int second = 0;
            if (t1 >= t2){
                first++;
            }
            if (t1 <= t2){
                second++;
            }
            sprintf(newbuffer, "%s\n%s\nverylongseparator\n%d\n%d", p1, p2, first, second);
            write(leaderboard, newbuffer, 50);
        }
    }
}
int start(int KEY){
    int shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
    int *start;
    start = shmat(shmd, 0, 0);
    *start = 0;

    int player0 = shmget(k0, sizeof(int), IPC_CREAT | 0640);
    int *time1;
    time1 = shmat(player0, 0, 0);
    *time1 = -1;

    int player1 = shmget(k1, sizeof(int), IPC_CREAT | 0640);
    int* time2;
    time2 = shmat(player1, 0, 0);
    *time2 = -1;

    int playerWords = shmget(657396715, sizeof(int) * 2, IPC_CREAT | 0640);
    int* word = shmat(playerWords, 0, 0);

    int playerNames = shmget(256773432, sizeof(char) * 30, IPC_CREAT | 0666);
    char* name = shmat(playerNames, 0, 0);

    char* first = "Player 1";
    char* second = "Player 2";
    for (int i = 0; i < strlen(first); i++){
        name[i] = first[i];
    }
    for (int i = 0; i < strlen(second); i++){
        name[i + 15] = second[i];
    }

    int semd = semget(KEY, 1, IPC_CREAT | 0660);
    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, 2);
    char* buffer;

    int flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);

    int leaderboard = open("./leaderboard.txt", O_RDWR | O_CREAT, 0666);

    while (1){
        signal(SIGINT, sighandler);
        buffer = typed();
        if (strcmp(buffer, "start") == 0){
            *start = 2;
            printf("Game has been started.\n");
            fflush(stdout);
        }
        if (strcmp(buffer, "score") == 0){
            checkScore();
            fflush(stdout);
        }
        if (strcmp(buffer, "update") == 0){
            updateScore("joe", "bob", 5, 6);
            printf("buffer is update\n");
            fflush(stdout);
        }
        if (*start == 2){
            int finished1 = 1;
            int finished2 = 1;
            while (*time1 == -1 || *time2 == -1){
                if (*time1 != -1 && finished1){
                    printf("0 made it\n");
                    printf("%s has finished in %d seconds\n", name, *time1);
                    finished1 = 0;
                }
                if (*time2 != -1 && finished2){
                    printf("1 made it\n");
                    printf("%s has finished in %d seconds\n", &name[15], *time2);
                    finished2 = 0;
                }
            }
            *time1 = -1;
            *time2 = -1;
        }
    }
}

int main(){
    int KEY = 1867821435;
    start(KEY);
}
