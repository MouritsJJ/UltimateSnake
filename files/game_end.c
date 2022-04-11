#include "../include.h"

/* The end screen function */
void game_end(int *quit, int totalscore, int totalscore1, int players){
    SDL_Window*   window  = NULL;
    SDL_Renderer* rend    = NULL;
    SDL_Surface*  surface = NULL;
    SDL_Texture*  bg      = NULL;
    SDL_Texture*  title   = NULL;
    SDL_Texture*  text    = NULL;
    SDL_Texture*  player1 = NULL;
    SDL_Texture*  player2 = NULL;
    SDL_Texture*  score   = NULL;
    SDL_Texture*  score1  = NULL;
    SDL_Texture*  con     = NULL;

    SDL_Color     color   = {0, 255, 0};
    SDL_Color     color1  = {0, 0, 255};

    TTF_Font*     font    = NULL;

    SDL_Event     event;

    SDL_Rect      title_rec, text_rec, con_rec; 
    SDL_Rect      player1_rec, player2_rec;
    SDL_Rect      score_rec, score1_rec, score2_rec;

    char score_text[20], score1_text[20];
    int enter = 0;

    /* Create window */
    window = create_window(640, 480);

    /* Create renderer */
    rend = create_renderer(window);

    /* Create background */
    bg = create_end_bg(surface, rend);

    /* Create title */
    title = create_end_title(rend, surface, &title_rec);

    /* Create score text */
    text = create_score_text(rend, surface, &text_rec, players);

    /* Create player text */
    player1 = create_end_player1(rend, surface, &player1_rec);
    player2 = create_end_player2(rend, surface, &player2_rec);

    /* Create score numbers */
    font = open_font(30, font);
    sprintf(score_text, "%d", totalscore);
    surface = TTF_RenderText_Blended(font, score_text, color);
    score = create_tex(rend, surface);
    SDL_QueryTexture(score, NULL, NULL, &score1_rec.w, &score1_rec.h);
    score1_rec.x = (640 - score1_rec.w) / 4 + 10;
    score1_rec.y = (480 - score1_rec.h) / 2 + 100;
    sprintf(score1_text, "%d", totalscore1);
    surface = TTF_RenderText_Blended(font, score1_text, color1);
    score1 = create_tex(rend, surface);
    SDL_QueryTexture(score1, NULL, NULL, &score2_rec.w, &score2_rec.h);
    score2_rec.x = (640 - score2_rec.w) / 2 + 130;
    score2_rec.y = (480 - score2_rec.h) / 2 + 100;

    score_rec.w = score1_rec.w;
    score_rec.h = score1_rec.h;
    score_rec.x = (640 - score_rec.w) / 2;
    score_rec.y = (480 - score_rec.h) / 2 + 50;
    TTF_CloseFont(font);

    /* Create continue text */
    con = create_con_text(rend, surface, &con_rec);

    /* Draw to screen */
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bg, NULL, NULL);
    SDL_RenderCopy(rend, title, NULL, &title_rec);
    SDL_RenderCopy(rend, text, NULL, &text_rec);
    SDL_RenderCopy(rend, con, NULL, &con_rec);
    if (players){
        SDL_RenderCopy(rend, player1, NULL, &player1_rec);
        SDL_RenderCopy(rend, score, NULL, &score1_rec);
        SDL_RenderCopy(rend, player2, NULL, &player2_rec);
        SDL_RenderCopy(rend, score1, NULL, &score2_rec);
    } else {
        SDL_RenderCopy(rend, score, NULL, &score_rec);
    }
    SDL_RenderPresent(rend);

    /* Animation loop */
    while (!(*quit) && !enter){
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                *quit = 1;
            if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
                    enter = 1;
        }
    }

    /* Clear ressources */
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(player1);
    SDL_DestroyTexture(player2);
    SDL_DestroyTexture(score);
    SDL_DestroyTexture(score1);
    SDL_DestroyTexture(con);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
}
