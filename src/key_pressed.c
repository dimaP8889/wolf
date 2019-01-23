#include "wolf.h"

/*
**		set objects pixels
*/

void	update_info(t_game *game)
{
	game->player.projection_plane.left_angle = game->player.point_of_view - (game->player.projection_plane.field_of_view / 2);
	game->player.projection_plane.right_angle = game->player.point_of_view + (game->player.projection_plane.field_of_view / 2);
}

void	set_object(t_game *game, int y, int x, int size)
{
	int		pixels_row;
	int		pixels_col;

	pixels_row = 0;
	pixels_col = 0;

	while (pixels_row < size)
	{
		while (pixels_col < size)
		{
			game->window.pixels[(y + pixels_row) * WIDTH + x + pixels_col] = 0xFFFFFF;
			pixels_col++;
		}
		pixels_col = 0;
		pixels_row++;
	}
}

/*
**		fill pixels
*/

void	fill_pixels(t_game *game)
{
	int	row_num;
	int	col_num;

	row_num = 0;
	col_num = 0;
	ft_memset(game->window.pixels, 0, HEIGHT * WIDTH * sizeof(Uint32));
	while (game->map[row_num])
	{
		while (game->map[row_num][col_num])
		{
			if (game->map[row_num][col_num] == '#')
				set_object(game, row_num * BLOCK, col_num * BLOCK, BLOCK);
			col_num++;
		}
		col_num = 0;
		row_num++;
	}
	set_object(game, game->player.position.y, game->player.position.x, game->player.size);
}

void	key_pressed(SDL_KeyboardEvent key, t_game *game)
{
	int x;

	x = 0;
	if (game->player.point_of_view >= 360)
		game->player.point_of_view -= 360;
	if (key.keysym.sym == SDLK_LEFT)
		game->player.point_of_view += game->player.projection_plane.angle_between_col * TURN;
	if (key.keysym.sym == SDLK_RIGHT)
		game->player.point_of_view -= game->player.projection_plane.angle_between_col * TURN;
	if (key.keysym.sym == SDLK_UP) {
		game->player.position.x += game->player.delta.x * MOVE;
		game->player.position.y += game->player.delta.y * MOVE;
	}
	if (key.keysym.sym == SDLK_DOWN) {
		game->player.position.x -= game->player.delta.x * MOVE;
		game->player.position.y -= game->player.delta.y * MOVE;
	}
	update_info(game);
	fill_pixels(game);
	cast_ray(game);
	printf("Left Angle: %f\n", game->player.projection_plane.left_angle);
	printf("Angle: %f\n", game->player.point_of_view);
	printf("Right Angle: %f\n", game->player.projection_plane.right_angle);
}