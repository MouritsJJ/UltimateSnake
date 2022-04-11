/* Prototypes */

/* Create background */
SDL_Texture* create_bg(SDL_Surface* surface, SDL_Renderer* rend);

/* Create title */
SDL_Texture* create_title(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create mode text */
SDL_Texture* create_mode_text(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create player 1 */
SDL_Texture* create_player1(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create player 2 */
SDL_Texture* create_player2(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Run for players */
void run_player(int *quit, int *player);

/* Run for modes */
void run_mode(int *quit, int *fast);

/* Create easy */
SDL_Texture* create_easy(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create Medium */
SDL_Texture* create_med(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create Hard */
SDL_Texture* create_hard(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create arrows */
SDL_Texture* create_arrows(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create wasd */
SDL_Texture* create_wasd(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create controls */
SDL_Texture* create_controls(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Run for controls */
void run_control(int *quit);


