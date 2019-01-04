#include "wolf.h"

/*
**		draw player
*/

void		draw(t_game game)
{
	SDL_UpdateTexture(game.window.texture, NULL, game.window.pixels, WIDTH * sizeof(Uint32));
	SDL_RenderClear(game.window.renderer);
	SDL_RenderCopy(game.window.renderer, game.window.texture, NULL, NULL);
	SDL_RenderPresent(game.window.renderer);
}