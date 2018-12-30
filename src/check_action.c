#include "wolf.h"

/*
**		check actions for screen
*/

int		check_action(t_game game)
{

	SDL_Event e;

	e = game.window.event;
	SDL_PollEvent(&e);
	if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN
		&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (0);
	return (1);
}