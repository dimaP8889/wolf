#include "wolf.h"

/*
**		set objects pixels
*/

void		update_info(t_game *game)
{
	game->player.projection_plane.left_angle = game->player.point_of_view - (PP_FIELD / 2);
	game->player.projection_plane.right_angle = game->player.point_of_view + (PP_FIELD / 2);
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

// counted all walls heights

int* 		count_objects_heights(t_game *game)
{
	int 	i;
	int		*heights;

	i = 0;
	heights = (int*)malloc(sizeof(int) * PP_WIDTH + 1);
	while (i < PP_WIDTH)
	{
		heights[i] = ((float)game->player.projection_plane.dist_to_pp / (float)game->player.projection_plane.distances[i]) * (float)BLOCK;
		i++;
	}
	heights[i] = 0;
	return (heights);
}

// counted all walls positions (needs to impove)

int*		count_objects_positions(t_draw_params draw_params)
{
	int		i;
	int		*positions;

	i = 0;
	positions = (int*)malloc(sizeof(int) * PP_WIDTH + 1);
	while (i < PP_WIDTH)
	{
		positions[i] = ((float)PP_HEIGHT - (float)draw_params.heights[i]) / 2;
		i++;
	}
	positions[i] = 0;
	return (positions);
}

t_draw_params count_draw_params(t_game *game)
{
	t_draw_params	draw_params;

	draw_params.heights = count_objects_heights(game);
	draw_params.positions = count_objects_positions(draw_params);

	return (draw_params);
}



void 		set_line(int i, t_game *game, t_draw_params draw_params)
{
	int 	cur_height;
	int		step_width;
	int		cur_step_width;
	int		step_height;

	cur_height = 0;
	step_width = WIDTH / PP_WIDTH;
	step_height = HEIGHT / PP_HEIGHT;
	cur_step_width = 0;
	while (cur_height < HEIGHT)
	{
		while (cur_step_width < step_width)
		{
			if (cur_height / step_height >= draw_params.positions[i] && (HEIGHT - cur_height) / step_height >= draw_params.positions[i]) {
				game->window.pixels[(cur_height * WIDTH) + (i * step_width) + cur_step_width] = 0xFFFFFF;
			}
			cur_step_width++;
		}
		cur_step_width = 0;
		cur_height++;
	}
}



void		fill_pixels(t_game *game, t_draw_params draw_params)
{

	int		i;

	i = 0;
	ft_memset(game->window.pixels, 0, HEIGHT * WIDTH * sizeof(Uint32));
	while (i < PP_WIDTH)
	{
		set_line(i, game, draw_params);
		i++;
	}
}


/*
**		fill pixels
*/

void		fill_pixels_map(t_game *game)
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
	int 			x;
	t_draw_params	draw_params;

	x = 0;
	if (game->player.point_of_view >= 360)
		game->player.point_of_view -= 360;
	if (key.keysym.sym == SDLK_RIGHT)
		game->player.point_of_view += game->player.projection_plane.angle_between_col * TURN;
	if (key.keysym.sym == SDLK_LEFT)
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
	cast_ray(game);
	draw_params = count_draw_params(game);
	fill_pixels(game, draw_params);
	free(draw_params.heights);
	free(draw_params.positions);


	// printf("Left Angle: %f\n", game->player.projection_plane.left_angle);
	// printf("Angle: %f\n", game->player.point_of_view);
	// printf("Right Angle: %f\n", game->player.projection_plane.right_angle);
}