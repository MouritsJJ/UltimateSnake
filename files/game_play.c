#include "../include.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

/* Gameplay function */
void gameplay (int *quit, int *totalscore, int *totalscore1, int *score, int *score1, int *life, int *life1, int mode, int players){
    SDL_Window*   window     = NULL;
    SDL_Renderer* rend       = NULL;
    SDL_Surface*  surface    = NULL;
    SDL_Texture*  snake_head = NULL;
    SDL_Texture*  snake_leg  = NULL;
    SDL_Texture*  apple_tex  = NULL;
    SDL_Texture*  point      = NULL;
    SDL_Texture*  point1     = NULL;
    SDL_Rect      apple, score_box, score_box1;
    SDL_Event     event;
    TTF_Font*     font       = NULL;
    SDL_Color     color      = {0, 255, 0};
    SDL_Color     color1     = {0, 0, 255};

    const unsigned char* event1 = SDL_GetKeyboardState(NULL);

    /* Score info */
    char text[20], text1[20];

    /* Snake info */
    int x_pos, y_pos, x_vel, y_vel;
    int x_pos1, y_pos1, x_vel1, y_vel1;

    /* Direction info */
    int up = 0, down = 0, right = 0, left = 0;
    int up1 = 0, down1 = 0, right1 = 0, left1 = 0;

    /* Game state info */
    int depth = 10, speed = 200, fps = 20;
    int rec;

    /* Music files */
    Mix_Music* bg_music = NULL;
    Mix_Chunk* app = NULL;

    srand(time(0));

    /* Initialize audio systems */
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    bg_music = Mix_LoadMUS("res/sound/seal.wav");
    if (bg_music == NULL)
        printf("Could not start music: %s\n", SDL_GetError());
    app = Mix_LoadWAV("res/sound/apple.wav");

    /* Create window */
    window = create_window(SCREEN_WIDTH, SCREEN_HEIGHT);

    /* Create renderer */
    rend = create_renderer(window);

    if (mode == 1){
        depth = 20; speed = 160; fps = 8;
    } else if (mode == 2){
        depth = 20; speed = 300; fps = 15;
    } else if (mode == 3){
        depth = 10; speed = 500; fps = 50;
    }

    rec = (SCREEN_WIDTH * SCREEN_HEIGHT) / depth;
    SDL_Rect* snake = calloc(rec, sizeof(SDL_Rect));
    SDL_Rect* snake1 = calloc(rec, sizeof(SDL_Rect));
    
    /* Create snake head */
    surface = create_img_surface("res/pic/snake1.png");
    snake_head = create_tex(rend, surface);
    snake[0].w = snake[0].h = depth;
    if (players){
        surface = create_img_surface("res/pic/head1.png");
        snake_leg = create_tex(rend, surface);
        snake1[0].w = snake1[0].h = depth;

        x_pos  = (SCREEN_WIDTH  / 4);
        y_pos  = (SCREEN_HEIGHT / 4);
        x_pos1 = (SCREEN_WIDTH  / 2) + (SCREEN_WIDTH  / 4);
        y_pos1 = (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 4);
    } else {
        x_pos = (SCREEN_WIDTH)  / 2;
        y_pos = (SCREEN_HEIGHT) / 2;
    }

    zero_snake(snake, rec);
    zero_snake(snake1, rec);

    /* Create apple */
    surface = create_img_surface("res/pic/apple.png");
    apple_tex = create_tex(rend, surface);
    apple.w = apple.h = depth;
    first_apple(&apple, SCREEN_WIDTH, SCREEN_HEIGHT);

    /* Create score and life box */
    font    = open_font(30, font);
    score_box.x = 10;
    score_box.y = SCREEN_HEIGHT - 40;
    score_box.h = 30;
    score_box.w = 120;

    score_box1.x = SCREEN_WIDTH  - 130;
    score_box1.y = SCREEN_HEIGHT - 40;
    score_box1.h = 30;
    score_box1.w = 120;

    /* Start music */
    Mix_PlayMusic(bg_music, -1);
    Mix_VolumeMusic(20);

    /* Animation loop */
    while (!(*quit) && *life){
        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) *quit = 1;
        SDL_PumpEvents();
        if (players){
            switch_move_arrow(event1, &up, &down, &right, &left);
            switch_move_wasd(event1, &up1, &down1, &right1, &left1);
        } else {
            switch_move_arrow(event1, &up, &down, &right, &left);
            switch_move_wasd(event1, &up, &down, &right, &left);
        }

        /* Move snake */
        if (players){
            move_snake(&x_vel1, &y_vel1, speed, &up1, &down1, &right1, &left1);
            y_pos1 += y_vel1 / fps;
            x_pos1 += x_vel1 / fps;
        }
        move_snake(&x_vel, &y_vel, speed, &up, &down, &right, &left);
        y_pos += y_vel / fps;
        x_pos += x_vel / fps;

        /* Collision detection */
        if (players)
            collision_det(&x_pos1, &y_pos1, SCREEN_WIDTH, SCREEN_HEIGHT);
        collision_det(&x_pos, &y_pos, SCREEN_WIDTH, SCREEN_HEIGHT);

        /* Tail collision detection */
        if (players)
            tail_col_det(snake1, score1, x_pos1, y_pos1, life1);
        tail_col_det(snake, score, x_pos, y_pos, life);

        /* Player collision detection */
        if (players){
            *totalscore  += tail_col_det2(snake1, score1, score, x_pos, y_pos, life1);
            *totalscore1 += tail_col_det2(snake, score, score1, x_pos1, y_pos1, life);
        }

        /* Calc life */
        if (!(*life1))
            *life = 0;

        /* Create tail */
        if (players)
            create_tail(snake1, *score1);
        create_tail(snake, *score);

        if (players){
            snake1[0].y = y_pos1;
            snake1[0].x = x_pos1;
        }
        snake[0].y = y_pos;
        snake[0].x = x_pos;

        /* Print scores */
        sprintf(text, "Score %d lives %d", *score, *life);
        surface = TTF_RenderText_Blended(font, text, color);
        point = create_tex(rend, surface);
        if (players){
            sprintf(text1, "Score %d lives %d", *score1, *life1);
            surface = TTF_RenderText_Blended(font, text1, color1);
            point1 = create_tex(rend, surface);
        }

        /* Apple collection */
        if (players)
            *totalscore1 += apple_collection(app, &apple, snake1, score1, SCREEN_WIDTH, SCREEN_HEIGHT);
        *totalscore += apple_collection(app, &apple, snake, score, SCREEN_WIDTH, SCREEN_HEIGHT);
        
        /* Draw on screen */
        SDL_RenderClear(rend);
        if (players)
            render_snake(snake1, rend, snake_leg, *score1);
        render_snake(snake, rend, snake_head, *score);
        SDL_RenderCopy(rend, point, NULL, &score_box);
        SDL_RenderCopy(rend, point1, NULL, &score_box1);
        SDL_RenderCopy(rend, apple_tex, NULL, &apple);
        SDL_RenderPresent(rend);

        /* FPS */
        SDL_Delay(1000 / fps);
    }

    /* Clear ressources */
    SDL_DestroyTexture(point);
    SDL_DestroyTexture(point1);
    SDL_DestroyTexture(snake_head);
    SDL_DestroyTexture(snake_leg);
    SDL_DestroyTexture(apple_tex);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(bg_music);
    Mix_FreeChunk(app);
    Mix_CloseAudio();
}
