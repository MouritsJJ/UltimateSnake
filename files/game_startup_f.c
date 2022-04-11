#include "../include.h"

/* Create background */
SDL_Texture* create_bg(SDL_Surface* surface, SDL_Renderer* rend){
    surface = IMG_Load("res/pic/snake_bg.png");
    if (!surface){
        printf("Surface was not created. SDL_Error: %s\n", SDL_GetError());
    }
    return create_tex(rend, surface);
}

/* Create title */
SDL_Texture* create_title(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(60, font);
    surface = TTF_RenderText_Blended(font, "Welcome To Ultimate Snake", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = (480 - rec->h) / 8;
    TTF_CloseFont(font);
    return tex;
}

/* Create mode text */
SDL_Texture* create_mode_text(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {170, 0, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(45, font);
    surface = TTF_RenderText_Blended(font, "Choose Gamemode", color);
    tex = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = (480 - rec->h) / 2 + 50;
    TTF_CloseFont(font);
    return tex;
}

/* Create player 1 */
SDL_Texture* create_player1(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(30, font);
    surface = TTF_RenderText_Blended(font, "1 Player", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 - 100;
    rec->y = (480 - rec->h) / 2 + 150;
    TTF_CloseFont(font);
    return tex;
}

/* Create player 2 */
SDL_Texture* create_player2(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(30, font);
    surface = TTF_RenderText_Blended(font, "2 Player", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 + 100;
    rec->y = (480 - rec->h) / 2 + 150;
    TTF_CloseFont(font);
    return tex;
}

/* Run for players */
void run_player(int *quit, int *player){
    SDL_Event event;
    while (!*quit && !*player){
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                *quit = 1;
            } else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_1) *player = 1;
                if (event.key.keysym.scancode == SDL_SCANCODE_2) *player = 2;
            }
        }
    }
    if (*player == 2)
        *player = 1;
    else
        *player = 0;    
}

/* Run for modes */
void run_mode(int *quit, int *fast){
    SDL_Event event;
    while (!*quit && !*fast){
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                *quit = 1;
            } else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.scancode == SDL_SCANCODE_1) *fast = 1;
                if (event.key.keysym.scancode == SDL_SCANCODE_2) *fast = 2;
                if (event.key.keysym.scancode == SDL_SCANCODE_3) *fast = 3;
            }
        }
    }
}

/* Create easy */
SDL_Texture* create_easy(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(30, font);
    surface = TTF_RenderText_Blended(font, "Easy", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 - 100;
    rec->y = (480 - rec->h) / 2 + 150;
    TTF_CloseFont(font);
    return tex;
}

/* Create Medium */
SDL_Texture* create_med(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(30, font);
    surface = TTF_RenderText_Blended(font, "Medium", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = (480 - rec->h) / 2 + 150;
    TTF_CloseFont(font);
    return tex;
}

/* Create Hard */
SDL_Texture* create_hard(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(30, font);
    surface = TTF_RenderText_Blended(font, "Hard", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 + 100;
    rec->y = (480 - rec->h) / 2 + 150;
    TTF_CloseFont(font);
    return tex;
}

/* Create arrows */
SDL_Texture* create_arrows(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(25, font);
    surface = TTF_RenderText_Blended(font, "W A S D", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 - 100;
    rec->y = (480 - rec->h) / 2 + 190;
    TTF_CloseFont(font);
    return tex;
}

/* Create wasd */
SDL_Texture* create_wasd(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {0, 210, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(25, font);
    surface = TTF_RenderText_Blended(font, "Arrow Keys", color);
    tex     = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2 + 100;
    rec->y = (480 - rec->h) / 2 + 190;
    TTF_CloseFont(font);
    return tex;
}

/* Create controls */
SDL_Texture* create_controls(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec){
    SDL_Color color = {170, 0, 20};
    TTF_Font* font = NULL;
    SDL_Texture*  tex = NULL;

    font    = open_font(45, font);
    surface = TTF_RenderText_Blended(font, "Controls", color);
    tex = create_tex(rend, surface);
    SDL_QueryTexture(tex, NULL, NULL, &rec->w, &rec->h);
    rec->x = (640 - rec->w) / 2;
    rec->y = (480 - rec->h) / 2 + 50;
    TTF_CloseFont(font);
    return tex;
}

/* Run for controls */
void run_control(int *quit){
    SDL_Event event;
    int i = 0;
    while (!*quit && !i){
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                *quit = 1;
            } else if (event.type == SDL_KEYDOWN) i = 1;
        }
    }
}
