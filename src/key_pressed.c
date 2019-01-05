#include "wolf.h"

/*
**		set wall
*/

void	set_object(t_game game, int y, int x, int size)
{
	int		pixels_row;
	int		pixels_col;

	pixels_row = 0;
	pixels_col = 0;
	while (pixels_row < size)
	{
		while (pixels_col < size)
		{
			game.window.pixels[(y * size + pixels_row) * WIDTH + (x * y + pixels_col)] = 0x0000FF;
			pixels_col++;
		}
		pixels_col = 0;
		pixels_row++;
	}
}



/*
**		fill pixels
*/

void	fill_pixels(t_game game)
{
	int	row_num;
	int	col_num;

	row_num = 0;
	col_num = 0;
	while (game.map[row_num])
	{
		while (game.map[row_num][col_num])
		{
			if (game.map[row_num][col_num] == '#')
				set_object(game, row_num, col_num, game.block_size);
			col_num++;
		}
		col_num = 0;
		row_num++;
	}
}

void	key_pressed(SDL_KeyboardEvent key, t_game *game)
{
	int x;

	x = 0;
	if (key.keysym.sym == SDLK_LEFT)
	{
	    for (int i = 0; i < HEIGHT; ++i)
    	{
    		for (int j = 0; j < WIDTH; ++j)
    		{
    			if (j < WIDTH / 2)
    				game->window.pixels[x] = 255;
    			x++;
			}
		}
		printf("%i\n", x);
	}
	if (key.keysym.sym == SDLK_RIGHT)
		printf("right\n");
	if (key.keysym.sym == SDLK_UP)
		printf("up\n");
	if (key.keysym.sym == SDLK_DOWN)
		printf("down\n");
}