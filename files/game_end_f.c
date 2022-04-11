#include "../include.h"

/* Create end bg */
SDL_Texture* create_end_bg(SDL_Surface* surface, SDL_Renderer* rend){
    surface = IMG_Load("res/pic/snake_bg.png");
    if (!surface){
        printf("Surface was not created. SDL_Error: %s\n", SDL_GetError());
    }
    return create_tex(rend, surface);
}

/* Create title */
SDL_Texture* create_end_title(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(60, font);
    surface = TTF_RenderText_Blended(font, "Game Over", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = (480 - rec->h) / 8;
    TTF_CloseFont(font);
    return tex;
}

/* Create score text */
SDL_Texture* create_score_text(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec, int players){
    SDL_Color color = {170, 0, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(45, font);
    if (players)
        surface = TTF_RenderText_Blended(font, "Scores", color);
    else
        surface = TTF_RenderText_Blended(font, "Score", color);
    tex = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = (480 - rec->h) / 2 - 50;
    TTF_CloseFont(font);
    return tex;
}

/* Create player 1 */
SDL_Texture* create_end_player1(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 255, 0};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(35, font);
    surface = TTF_RenderText_Blended(font, "Player 1", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 4;
    rec->y = (480 - rec->h) / 2 + 50;
    TTF_CloseFont(font);
    return tex;
}

/* Create player 2 */
SDL_Texture* create_end_player2(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 0, 255};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(35, font);
    surface = TTF_RenderText_Blended(font, "Player 2", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 + 130;
    rec->y = (480 - rec->h) / 2 + 50;
    TTF_CloseFont(font);
    return tex;
}

/* Create continue text */
SDL_Texture* create_con_text(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(30, font);
    surface = TTF_RenderText_Blended(font, "Hit enter to play again", color);
    tex = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = 480 - (rec->h + 10);
    TTF_CloseFont(font);
    return tex;
}
