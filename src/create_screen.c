#include "wolf.h"

/*
**		create screen
*/

t_window	 create_screen()
{
	t_window	window;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		ft_printf("%s\n", SDL_GetError());
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE,
		&window.screen, &window.renderer))
		ft_printf("%s\n", SDL_GetError());

	return (window);
}