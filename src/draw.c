#include "wolf.h"

/*
**		draw player
*/

void		draw(t_game game)
{
	SDL_UpdateTexture(game.window.texture, NULL, game.window.pixels, WIDTH * sizeof(Uint32));
	//SDL_SetRenderDrawColor(game.window.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderCopy(game.window.renderer, game.window.texture, NULL, NULL);
	SDL_SetRenderDrawColor(game.window.renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(game.window.renderer, game.player.position.x, game.player.position.y, game.player.line.x, game.player.line.y);
	SDL_RenderPresent(game.window.renderer);
	SDL_RenderClear(game.window.renderer);
}