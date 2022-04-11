/* Prototypes */

/* Initialize SDL */
void init_SDL(void);

/* Create window */
SDL_Window* create_window(int width, int height);

/* Create renderer */
SDL_Renderer* create_renderer(SDL_Window* window);

/* Create IMG rectangle */
SDL_Surface* create_img_surface(char* img);

/* Create texture */
SDL_Texture* create_tex(SDL_Renderer* rend, SDL_Surface* surface);

/* Zero snake values */
void zero_snake(SDL_Rect snake[], int l);

/* Switch for wasd move */
void switch_move_wasd(const unsigned char* event1, int *up, int *down, int *right, int *left);

/* Switch for arrow move */
void switch_move_arrow(const unsigned char* event1, int *up, int *down, int *right, int *left);

/* Collision detection */
void collision_det(int *x_pos, int *y_pos, int width, int height);

/* Apple collection */
int apple_collection(Mix_Chunk* app, SDL_Rect* apple, SDL_Rect snake[], int *score, int width, int height);

/* First apple */
void first_apple(SDL_Rect *apple, int width, int height);

/* Move snake */
void move_snake(int *x_vel, int *y_vel, int speed, int *up, int *down, int *right, int *left);

/* Tail collision detection */
void tail_col_det(SDL_Rect snake[], int *score, int x_pos, int y_pos, int *life);

/* Tail collision detection for 2 players */
int tail_col_det2(SDL_Rect snake[], int *score, int *score1, int x_pos, int y_pos, int* life);

/* Create tail */
void create_tail(SDL_Rect snake[], int score);

/* Render snake */
void render_snake(SDL_Rect snake[], SDL_Renderer *rend, SDL_Texture *snake_head, int score);

/* Open font */
TTF_Font* open_font(int size, TTF_Font* font);


