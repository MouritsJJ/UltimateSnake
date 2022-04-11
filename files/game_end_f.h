/* Prototypes */

/* Create end bg */
SDL_Texture* create_end_bg(SDL_Surface* surface, SDL_Renderer* rend);

/* Create title */
SDL_Texture* create_end_title(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create score text */
SDL_Texture* create_score_text(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec, int players);

/* Create player 1 */
SDL_Texture* create_end_player1(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create player 2 */
SDL_Texture* create_end_player2(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);

/* Create continue text */
SDL_Texture* create_con_text(SDL_Renderer* rend, SDL_Surface* surface, SDL_Rect* rec);


