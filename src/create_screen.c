#include "wolf.h"

/*
**		create screen
*/

t_window	 create_screen()
{
	t_window	window;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error_message(SDL_GetError());
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE,
		&window.screen, &window.renderer))
		error_message(SDL_GetError());
	window.texture = SDL_CreateTexture(window.renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	if (!window.texture)
		error_message(SDL_GetError());
	window.pixels = (Uint32*)malloc(sizeof(Uint32) * (WIDTH * HEIGHT));
	ft_memset(window.pixels, 0, HEIGHT * WIDTH * sizeof(Uint32));
	return (window);
}