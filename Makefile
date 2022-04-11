
CFLAGS = -Wall -ansi -pedantic
O_name = -o snake
SDL = -I ../../include -L ../../lib -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
Files = snake.c
Startup = files/game_startup.c files/game_startup_f.c
Gameplay = files/game_play.c files/player.c
Gameend = files/game_end.c files/game_end_f.c
Highscore = files/highscore.c

game: snake.c
	gcc $(Files) $(Startup) $(Gameplay) $(Gameend) $(Highscore) $(O_name) $(CFLAGS) $(SDL)

