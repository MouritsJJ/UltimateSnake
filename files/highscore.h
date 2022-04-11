/* Prototypes */
    struct player {
        char player[20];
        int score;
        char mode[10];
    };
    typedef struct player player;

/* Highscore function for 1 player games */
void highscores1player(int score, int mode);

/* Highscore function for 2 player games */
void highscores2player(int score, int score1, int mode);

/* Read file and data for 2 player games */
int get_plays1(FILE* file, player plays[]);

/* Print data into file for 2 player games */
void print_plays1(FILE* file, player plays[], int len);

/* Read file and data for 1 player games */
int get_plays(FILE* file, player plays[]);

/* Print data into file for 1 player games */
void print_plays(FILE* file, player plays[], int len);

/* Compare function for qsort */
int cmp (const void* ep1, const void* ep2);

