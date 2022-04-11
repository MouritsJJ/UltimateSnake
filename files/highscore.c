#include "../include.h"

/* Highscore function for 1 player games */
void highscores1player(int score, int mode){
    FILE* file;
    player plays[101];

    char easy[] = "easy",
         med[]  = "medium",
         hard[] = "hard";
    
    int len = 0;

    /* Assign values to players */
    plays[0].score = score;
    if (mode == 1)
        strcpy(plays[0].mode, easy);
    else if (mode == 2)
        strcpy(plays[0].mode, med);
    else if (mode == 3)
        strcpy(plays[0].mode, hard);

    file = fopen("highscores1player", "r");
    if (file == NULL){
        fclose(file);
        file = fopen("highscores1player", "w");
        print_plays(file, plays, 1);
    } else {
        len = get_plays(file, plays);
        fclose(file);
        file = fopen("highscores1player", "w");
        print_plays(file, plays, len);
    }
    fclose(file);
}

/* Highscore function for 2 player games */
void highscores2player(int score, int score1, int mode){
    FILE* file;
    player plays[102];

    char easy[] = "easy",
         med[]  = "medium",
         hard[] = "hard";
    
    char player1[] = "Player1",
         player2[] = "Player2";
    
    int len = 0;

    /* Assign values to players */
    plays[0].score = score;
    plays[1].score = score1;
    strcpy(plays[0].player, player1);
    strcpy(plays[1].player, player2);
    if (mode == 1){
        strcpy(plays[0].mode, easy);
        strcpy(plays[1].mode, easy);
    } else if (mode == 2){
        strcpy(plays[0].mode, med);
        strcpy(plays[1].mode, med);
    } else if (mode == 3){
        strcpy(plays[0].mode, hard);
        strcpy(plays[1].mode, hard);
    }

    file = fopen("highscores2player", "r");
    if (file == NULL){
        fclose(file);
        file = fopen("highscores2player", "w");
        print_plays1(file, plays, 2);
    } else {
        len = get_plays1(file, plays);
        fclose(file);
        file = fopen("highscores2player", "w");
        print_plays1(file, plays, len);
    }
    fclose(file);
}

/* Read file and data for 2 player games */
int get_plays1(FILE* file, player plays[]){
    int c, i = 0, j = 2;
    char line[100];
    
    while ((c = fgetc(file)) != '\n')
    c = fgetc(file);
    while ((c = fgetc(file)) != EOF){
        ungetc(c, file);
        while ((c = fgetc(file)) != '\n' && c != EOF){
            line[i++] = c;
        } line[i] = '\0'; i = 0;
        sscanf(line, "%*d%d%s%s", &plays[j].score, plays[j].player, plays[j].mode);
        j++;
    }
    return j;
}

/* Print data into file for 2 player games */
void print_plays1(FILE* file, player plays[], int len){
    int i;
    qsort(plays, len, sizeof(player), cmp);
    fprintf(file, "%-10s%-10s%-10s%-10s\n", "Rank", "Score", "Player", "Mode");
    for (i = 0; i < len && i < 100; i++){
        fprintf(file, "%-10d%-10d%-10s%-10s\n", i + 1, plays[i].score, plays[i].player, plays[i].mode);
    }

}

/* Read file and data for 1 player games */
int get_plays(FILE* file, player plays[]){
    int c, i = 0, j = 1;
    char line[100];
    
    while ((c = fgetc(file)) != '\n')
    c = fgetc(file);
    while ((c = fgetc(file)) != EOF){
        ungetc(c, file);
        while ((c = fgetc(file)) != '\n' && c != EOF){
            line[i++] = c;
        } line[i] = '\0'; i = 0;
        sscanf(line, "%*d%d%s", &plays[j].score, plays[j].mode);
        j++;
    }
    return j;
}

/* Print data into file for 1 player games */
void print_plays(FILE* file, player plays[], int len){
    int i;
    qsort(plays, len, sizeof(player), cmp);
    fprintf(file, "%-10s%-10s%-10s\n", "Rank", "Score", "Mode");
    for (i = 0; i < len && i < 100; i++){
        fprintf(file, "%-10d%-10d%-10s\n", i + 1, plays[i].score, plays[i].mode);
    }

}

/* Compare function for qsort */
int cmp (const void* ep1, const void* ep2){
    player *tp1 = (player*)ep1,
           *tp2 = (player*)ep2;
    
    if (tp1->score < tp2->score){
        return 1;
    } else if (tp1->score > tp2->score){
        return -1;
    } else {
        return 0;
    }
}


