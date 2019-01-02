#include "wolf.h"

void	key_pressed(SDL_KeyboardEvent key, t_game game)
{

	if (key.keysym.sym == SDLK_LEFT)
	    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    	{
			game.window.pixels[i] = 0x0000FF;
		}
	if (key.keysym.sym == SDLK_RIGHT)
		printf("right\n");
	if (key.keysym.sym == SDLK_UP)
		printf("up\n");
	if (key.keysym.sym == SDLK_DOWN)
		printf("down\n");
	SDL_UpdateTexture(game.window.texture, NULL, game.window.pixels, WIDTH * sizeof(Uint32));
	SDL_RenderClear(game.window.renderer);
    SDL_RenderCopy(game.window.renderer, game.window.texture, NULL, NULL);
    SDL_RenderPresent(game.window.renderer);
}