#include "include.h"

int main (int argc, char* argv[]){
    /* Game state info */
    int quit = 0, players, mode;
    int score, life, score1, life1;
    int totalscore, totalscore1;

    system("osascript -e 'tell application \"System Events\""
                        "to tell process \"Terminal\""
                        "to keystroke \"k\" using command down'");
    system("osascript -e 'tell application \"System Events\""
                        "to tell process \"Terminal\""
                        "to keystroke \"m\" using command down'");

    /* Initialize SDL */
    init_SDL();

    do {
        /* Set gamestate */
        players = mode = 0;
        score = score1 = 0;
        totalscore = totalscore1 = 0;
        life = life1 = 3;

        /* Game Startup */
        game_startup(&quit, &players, &mode);

        /* Gameplay */
        gameplay(&quit, &totalscore, &totalscore1, &score, &score1, &life, &life1, mode, players);
        
        /* Game End */
        game_end(&quit, totalscore, totalscore1, players);

        /* Highscores */
        if (players)
            highscores2player(totalscore, totalscore1, mode);
        else
            highscores1player(totalscore, mode);

    } while (!quit);

    /* Clear ressources */
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
