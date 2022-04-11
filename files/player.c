#include "../include.h"

/* Initialize SDL */
void init_SDL(void){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    if (TTF_Init() != 0){
        printf("TTF could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
}

/* Create window */
SDL_Window* create_window(int width, int height){
    SDL_Window* window = SDL_CreateWindow("Ultimate Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              width, height, 0);
    if (!window){
        printf("Windows could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
    }
    return window;
}

/* Create renderer */
SDL_Renderer* create_renderer(SDL_Window* window){
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    return rend;
}

/* Create IMG rectangle */
SDL_Surface* create_img_surface(char* img){
    SDL_Surface* surface = IMG_Load(img);
    if(!surface){
        printf("Error creating surface: %s\n", SDL_GetError());
    }
    return surface;
}

/* Create texture */
SDL_Texture* create_tex(SDL_Renderer* rend, SDL_Surface* surface){
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex){
        printf("Error creating texture: %s\n", SDL_GetError());
    }
    return tex;
}

/* Zero snake values */
void zero_snake(SDL_Rect snake[], int l){
    int i;
    for (i = 0; i < l; i++){
        snake[i].x = -100; snake[i].y = -100;
    }
}

/* Switch for wasd move */
void switch_move_wasd(const unsigned char* event1, int *up, int *down, int *right, int *left){
    if (event1[SDL_SCANCODE_W]){
        if (!*down) {
            *up = 1; *down = *right = *left = 0;
        }
    } else if (event1[SDL_SCANCODE_S]){
        if (!*up) {
            *down = 1; *up = *right = *left = 0;
        }
    } if (event1[SDL_SCANCODE_A]){
        if (!*right){
            *left = 1; *down = *right = *up = 0;
        }
    } else if (event1[SDL_SCANCODE_D]){
        if (!*left) {
            *right = 1; *down = *up = *left = 0;
        }
    }
}

/* Switch for arrow move */
void switch_move_arrow(const unsigned char* event1, int *up, int *down, int *right, int *left){
    if (event1[SDL_SCANCODE_UP]){
        if (!*down) {
            *up = 1; *down = *right = *left = 0;
        }
    } else if (event1[SDL_SCANCODE_DOWN]){
        if (!*up) {
            *down = 1; *up = *right = *left = 0;
        }
    } if (event1[SDL_SCANCODE_LEFT]){
        if (!*right){
            *left = 1; *down = *right = *up = 0;
        }
    } else if (event1[SDL_SCANCODE_RIGHT]){
        if (!*left) {
            *right = 1; *down = *up = *left = 0;
        }
    }
}

/* Collision detection */
void collision_det(int *x_pos, int *y_pos, int width, int height){
    if (*x_pos <= 0)      *x_pos += width;
    if (*y_pos <= 0)      *y_pos += height;
    if (*x_pos >= width)  *x_pos =  0;
    if (*y_pos >= height) *y_pos =  0;
}

/* Apple collection */
int apple_collection(Mix_Chunk* app, SDL_Rect* apple, SDL_Rect snake[], int *score, int width, int height){
    int apple_rand, i, n = 0;
    if (apple->x == snake[0].x && apple->y == snake[0].y){
        Mix_PlayChannel(-1, app, 0);
        (*score) += 4; n = 4;
        apple_rand = rand();
        apple->x = (apple_rand % width)  - (apple_rand % apple->w);
        apple_rand = rand();
        apple->y = (apple_rand % height) - (apple_rand % apple->h);
    }
    for (i = 0; i <= *score; i++){
        if (apple->x == snake[i].x && apple->y == snake[i].y){
            apple_rand = rand();
            apple->x = (apple_rand % width)  - (apple_rand % apple->w);
            apple_rand = rand();
            apple->y = (apple_rand % height) - (apple_rand % apple->h);
            apple_collection(app, apple, snake, score, width, height);
        }
    }
    return n;
}

/* First apple */
void first_apple(SDL_Rect *apple, int width, int height){
    int apple_rand;
    apple_rand = rand();
    apple->x = (apple_rand % width)  - (apple_rand % apple->w);
    apple_rand = rand();
    apple->y = (apple_rand % height) - (apple_rand % apple->h);
}

/* Move snake */
void move_snake(int *x_vel, int *y_vel, int speed, int *up, int *down, int *right, int *left){
    *x_vel = *y_vel = 0;
    if (*up    && !*down ) *y_vel = -speed;
    if (*down  && !*up   ) *y_vel =  speed;
    if (*left  && !*right) *x_vel = -speed;
    if (*right && !*left ) *x_vel =  speed;
}

/* Tail collision detection */
void tail_col_det(SDL_Rect snake[], int *score, int x_pos, int y_pos, int *life){
    int i, n = *score;
    for (i = 0; i < *score; i++){
        if (x_pos == snake[i].x && y_pos == snake[i].y){
            *score = i;
            *life -= 1;
        }
    }
    for (; i <= n; i++){
        snake[i].x = -100; snake[i].y = -100;
    }
}

/* Tail collision detection for 2 players */
int tail_col_det2(SDL_Rect snake[], int *score, int *score1, int x_pos, int y_pos, int* life){
    int i, n = *score, j = 0;
    for (i = 0; i < *score; i++){
        if (x_pos == snake[i].x && y_pos == snake[i].y){
            *score1 += *score - i;
            j = *score - i;
            *score = i;
            *life -= 1;
        }
    }
    for (; i <= n; i++){
        snake[i].x = -100; snake[i].y = -100;
    }
    return j;
}

/* Create tail */
void create_tail(SDL_Rect snake[], int score){
    int i;
    for (i = score; i > 0; i--){
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
        snake[i].w = snake[0].w;
        snake[i].h = snake[0].h;
    }
}

/* Render snake */
void render_snake(SDL_Rect snake[], SDL_Renderer *rend, SDL_Texture *snake_head, int score){
    int i;
    for (i = 0; i <= score; i++){
        SDL_RenderCopy(rend, snake_head, NULL, &snake[i]);
    }
}

/* Open font */
TTF_Font* open_font(int size, TTF_Font* font){
    font    = TTF_OpenFont("res/font/snake.ttf", size);
    if (!font)
        printf("Font was not found. SDL_Error: %s\n", SDL_GetError());
    return font;
}    

