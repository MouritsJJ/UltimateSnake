#include "../include.h"

void game_startup(int *quit, int *player, int *fast){
    SDL_Window*   window   = NULL;
    SDL_Renderer* rend     = NULL;
    SDL_Surface*  surface  = NULL;
    SDL_Texture*  tex      = NULL;
    SDL_Texture*  bg       = NULL;
    SDL_Texture*  mode     = NULL;
    SDL_Texture*  player1  = NULL;
    SDL_Texture*  player2  = NULL;
    SDL_Texture*  easy     = NULL;
    SDL_Texture*  med      = NULL;
    SDL_Texture*  hard     = NULL;
    SDL_Texture*  wasd     = NULL;
    SDL_Texture*  arrow    = NULL;
    SDL_Texture*  controls = NULL;
    SDL_Rect      title, mode_rec, player1_rec,
                  player2_rec, easy_rec, med_rec, hard_rec;

    /* Create window */
    window = create_window(640, 480);

    /* Create renderer */
    rend = create_renderer(window);

    /* Create background */
    bg = create_bg(surface, rend);

    /* Create title */
    tex = create_title(rend, surface, &title);

    /* Create mode text */
    mode = create_mode_text(rend, surface, &mode_rec);

    /* Create player modes */
    player1 = create_player1(rend, surface, &player1_rec);
    player2 = create_player2(rend, surface, &player2_rec);
    
    /* Draw textures */
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_RenderCopy(rend, tex, NULL, &title);
    SDL_RenderCopy(rend, mode, NULL, &mode_rec);
    SDL_RenderCopy(rend, player1, NULL, &player1_rec);
    SDL_RenderCopy(rend, player2, NULL, &player2_rec);
    SDL_RenderPresent(rend);

    /* Run for players */
    run_player(quit, player);

    /* Create game modes */
    easy = create_easy(rend, surface, &easy_rec);
    med  = create_med(rend, surface, &med_rec);
    hard = create_hard(rend, surface, &hard_rec);

    /* Draw textures */
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_RenderCopy(rend, tex, NULL, &title);
    SDL_RenderCopy(rend, mode, NULL, &mode_rec);
    SDL_RenderCopy(rend, easy, NULL, &easy_rec);
    SDL_RenderCopy(rend, med, NULL, &med_rec);
    SDL_RenderCopy(rend, hard, NULL, &hard_rec);
    SDL_RenderPresent(rend);

    /* Run for modes */
    run_mode(quit, fast);

    /* Create controls */
    controls = create_controls(rend, surface, &mode_rec);
    arrow = create_arrows(rend, surface, &easy_rec);
    wasd = create_wasd(rend, surface, &hard_rec);

    /* Draw textures */
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_RenderCopy(rend, tex, NULL, &title);
    SDL_RenderCopy(rend, controls, NULL, &mode_rec);
    if (*player == 2){
        SDL_RenderCopy(rend, player1, NULL, &player1_rec);
        SDL_RenderCopy(rend, player2, NULL, &player2_rec);
    }
    SDL_RenderCopy(rend, arrow, NULL, &easy_rec);
    SDL_RenderCopy(rend, wasd, NULL, &hard_rec);
    SDL_RenderPresent(rend);

    /* Display for controls */
    run_control(quit);

    /* Clear ressources */
    SDL_DestroyTexture(arrow);
    SDL_DestroyTexture(wasd);
    SDL_DestroyTexture(controls);
    SDL_DestroyTexture(hard);
    SDL_DestroyTexture(med);
    SDL_DestroyTexture(easy);
    SDL_DestroyTexture(player2);
    SDL_DestroyTexture(player1);
    SDL_DestroyTexture(mode);
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(bg);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
}
