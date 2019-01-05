#include "wolf.h"

/*
**		create screen
*/

t_window	 create_screen()
{
	t_window	window;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error_message(SDL_GetError());
	if (!(window.window = SDL_CreateWindow("wolf", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		error_message(SDL_GetError());
	if (!(window.renderer = SDL_CreateRenderer(window.window, -1,
			SDL_RENDERER_ACCELERATED)))
		error_message(SDL_GetError());
	window.texture = SDL_CreateTexture(window.renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	if (!window.texture)
		error_message(SDL_GetError());
	window.pixels = (Uint32*)malloc(sizeof(Uint32) * (WIDTH * HEIGHT) + 1);
	ft_memset(window.pixels, 0, HEIGHT * WIDTH * sizeof(Uint32));
	return (window);
}