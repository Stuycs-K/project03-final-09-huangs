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
        int starter = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
        int *start;
        start = shmat(starter, 0, 0);
        *start = -1000;
        int p1 = shmget(k0, sizeof(int), IPC_CREAT | 0640);
        shmctl(p1, IPC_RMID, 0);
        int p2 = shmget(k1, sizeof(int), IPC_CREAT | 0640);
        shmctl(p2, IPC_RMID, 0);
        int playerWords = shmget(657396715, sizeof(int) * 2, IPC_CREAT | 0640);
        shmctl(playerWords, IPC_RMID, 0);
        int playerNames = shmget(256773432, sizeof(char*) * 2, IPC_CREAT | 0640);
        shmctl(playerNames, IPC_RMID, 0);
        remove("./score.txt");
        printf("\nYou have quit. Removing all players.\n");
        int semd = semget(KEY, sizeof(int), IPC_CREAT | 0640);
        semctl(semd, IPC_RMID, 0);
        usleep(1000);
        exit(0);
    }
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
void updateScore(char* p1, char* p2, int t1, int t2){
    int score = open("./score.txt", O_RDWR | O_CREAT, 0666);
    char* buffer = calloc(50, sizeof(char));
    int r = read(score, buffer, 50);
    char* newbuffer = calloc(50, sizeof(char));
    close(score);
    score = open("./score.txt", O_TRUNC | O_RDWR | O_CREAT, 0666);
    if (strlen(buffer) == 0){
        int first = 0;
        int second = 0;
        if (t1 < t2 && t1 > 0){
            first++;
        }
        else if (t1 != t2){
            second++;
        }
        sprintf(newbuffer, "%s\n%s\nverylongseparator\n%d\n%d", p1, p2, first, second);
        write(score, newbuffer, 50);
    }
    else{
        char* numbers = strstr(buffer, "verylongseparator") + 18;
        char* currentnumber;
        char* currentname = strsep(&buffer, "\n");
        char* nextname = strsep(&buffer, "\n");
        if (strcmp(currentname, p1) == 0 && strcmp(nextname, p2) == 0){
            char* firstscore = strsep(&numbers, "\n");
            int first = atoi(firstscore);
            int second = atoi(strsep(&numbers, "\n"));
            if (t1 < t2 && t1 > 0){
                first++;
            }
            else if (t1 != t2){
                second++;
            }
            sprintf(newbuffer, "%s\n%s\nverylongseparator\n%d\n%d", p1, p2, first, second);
            write(score, newbuffer, 50);
        }
        else{
            int first = 0;
            int second = 0;
            if (t1 < t2 && t1 > 0){
                first++;
            }
            else if (t1 != t2){
                second++;
            }
            sprintf(newbuffer, "%s\n%s\nverylongseparator\n%d\n%d", p1, p2, first, second);
            write(score, newbuffer, 50);
        }
    }
    close(score);
}
void playerQuit(int* time1, int* time2, char* name){
    if (*time1 == -1000){
        printf("%s has quit.\n", &name[15]);
        fflush(stdout);
        *time1 = -10000;
    }
    if (*time2 == -1000){
        printf("%s has quit.\n", name);
        fflush(stdout);
        *time2 = -10000;
    }
}
char * hostTyped(){
    char * typed = calloc(15, sizeof(char));
    
    int player0 = shmget(k0, sizeof(int), IPC_CREAT | 0640);
    int *time1;
    time1 = shmat(player0, 0, 0);
    int player1 = shmget(k1, sizeof(int), IPC_CREAT | 0640);
    int* time2;
    time2 = shmat(player1, 0, 0);
    
    int playerNames = shmget(256773432, sizeof(char) * 30, IPC_CREAT | 0666);
    char* name = shmat(playerNames, 0, 0);
    while(read(0, typed, 15) == -1){
        playerQuit(time1, time2, name);
    }
    if (typed[strlen(typed) - 1] == '\n'){
    typed[strlen(typed) - 1] = '\0';
    }
    return typed;
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

    int score = open("./score.txt", O_RDWR | O_CREAT, 0666);
    system("clear");
    printf("You have started a game of Budget Typeracer.\n");
    printf("Type \"start\" to start the game.\n");
    printf("Type \"score\" to check the score.\n");
    printf("Type \"reset\" to reset the score.\n");
    while (1){
        signal(SIGINT, sighandler);
        buffer = hostTyped();
        fflush(stdout);
        if (strcmp(buffer, "start") == 0){
            if (semctl(semd, 0, GETVAL) != 0){
                printf("You need two players to start\n");
            }
            else{
                *start = 2;
                printf("Game has been started.\n");
            }
            fflush(stdout);
        }
        if (strcmp(buffer, "score") == 0){
            checkScore();
            fflush(stdout);
        }
        if (strcmp(buffer, "reset") == 0){
            remove("score.txt");
            int score = open("./score.txt", O_RDWR | O_CREAT, 0666);
            printf("The score has been reset.\n");
            fflush(stdout);
        }
        if (*start == 2){
            int finished1 = 1;
            int finished2 = 1;
            while (*time1 == -1 || *time2 == -1){
                if (*time1 > 0  && finished1){
                    printf("%s has finished in %d seconds\n", name, *time1);
                    finished1 = 0;
                }
                if (*time2 > 0 && finished2){
                    printf("%s has finished in %d seconds\n", &name[15], *time2);
                    finished2 = 0;
                }
                playerQuit(time1, time2, name);
            }
            updateScore(name, &name[15], *time1, *time2);
            *time1 = -1;
            *time2 = -1;
            *start = 0;
        }
    }
}

int main(){
    int KEY = 1867821435;
    start(KEY);
}
