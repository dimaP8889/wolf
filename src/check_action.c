#include "wolf.h"

/*
**		check actions for screen
*/

int		check_action(t_game *game)
{

	SDL_Event e;

	SDL_PollEvent(&e);
	if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN
		&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (0);
	else if (e.type == SDL_KEYUP){}
		//ft_printf("key_stoped\n");
	else if (e.type == SDL_KEYDOWN)
		key_pressed(e.key, game);
	return (1);
}