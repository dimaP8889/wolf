#include "wolf.h"

/*
**		find horizontal distances
*/

int				find_horizontal_dist(t_game *game, double angle)
{
	t_coordinates	A;
	t_coordinates	player;
	int				x_delta;
	int				y_delta;
	int				length;
	int				sign;

	sign = 1;
	player.x = game->player.position.x;
	player.y = game->player.position.y;
	if (angle >= 90 && angle < 270)
	{
		A.x = (player.x / BLOCK) * BLOCK - 1;
		x_delta = -BLOCK;
	} else {
		A.x = (player.x / BLOCK) * BLOCK + 64;
		x_delta = BLOCK;
	}
	A.y = player.y + (player.x - A.x) * tan(angle * RADIAN);
	y_delta = BLOCK * tan(angle * RADIAN);
	if (A.y / 64 >= game->map_size.y || A.y < 0) // check if out of range
		return (10000000);
	while (game->map[A.y / BLOCK][A.x / BLOCK] != '#')
	{
		A.x += x_delta;
		A.y += y_delta;
		if (A.y / 64 >= game->map_size.y || A.y < 0) // check if out of range
			return (10000000);
	}
	length = sqrt((player.x - A.x) * (player.x - A.x) + (player.y - A.y) * (player.y - A.y));
	//length = abs(player.x - A.x) / cos (angle * RADIAN);
	if (angle == game->player.point_of_view) // need to delete after
	{
		int len = sqrt((player.x - game->player.line.x) * (player.x - game->player.line.x) + (player.y - game->player.line.y) * (player.y - game->player.line.y));
		//printf("game->player.line.x: %d\n", length);
		printf("len: %d\n", len);
		printf("length: %d\n", length);
		printf("len: %d\n", len);
		if (len > length)
		{
			printf("horizontal x: %d\n", A.x);
			printf("horizontal y: %d\n", A.y);
			game->player.line = A;
		}
	}
	return (length);
}

/*
**		find vertical distances
*/

int				find_vertical_dist(t_game *game, double angle)
{
	t_coordinates	A;
	t_coordinates	player;
	int				x_delta;
	int				y_delta;
	int				length;
	int				sign;

	sign = 1;
	player.x = game->player.position.x;
	player.y = game->player.position.y;
	if (angle >= 0 && angle < 180)
	{
		A.y = (player.y / BLOCK) * BLOCK - 1;
		y_delta = -BLOCK;
	}
	else if (angle >= 180 && angle < 360)
	{
		A.y = (player.y / BLOCK) * BLOCK + 64;
		y_delta = BLOCK;
	}
	A.x = player.x + (player.y - A.y) / tan(angle * RADIAN);
	x_delta = BLOCK / tan(angle * RADIAN);
	if (A.x / 64 >= game->map_size.x || A.x < 0) // check if out of range
		return (10000000);
	while (game->map[A.y / BLOCK][A.x / BLOCK] != '#')
	{
		A.x += x_delta;
		A.y += y_delta;
		if (A.x / 64 >= game->map_size.x || A.x < 0) // check if out of range
			return (10000000);
	}
	if (angle == game->player.point_of_view) // need to delete after
	{
		// printf("vertical x: %d\n", A.x);
		// printf("vertical y: %d\n", A.y);
		game->player.line = A;
	}
	length = sqrt((player.x - A.x) * (player.x - A.x) + (player.y - A.y) * (player.y - A.y));
	//length = abs(player.x - A.x) / cos(angle * RADIAN);
	return (length);
}

/*
**		cast a ray to find distances to wall
*/

void	cast_ray(t_game *game)
{
	int					dist;
	int					dist_second;
	int					i;
	double				angle;
	
	i = 0;
	check_angles(game);
	angle = game->player.projection_plane.left_angle;
	while (i <= game->player.projection_plane.width)
	{
		check_angles(game);
		if (angle >= 360)
			angle = angle - 360;
		printf("POV : %f\n", game->player.point_of_view);
		printf("angle : %f\n", angle);
		printf("i : %i\n", i);
		dist = find_vertical_dist(game, angle);
		dist_second = find_horizontal_dist(game, angle);
		if (angle == game->player.point_of_view) {
			// printf("x: %i\n", game->player.line.x);
			// printf("x: %i\n", game->player.line.y);
		}
		game->player.projection_plane.distances[i] = dist < dist_second ? dist : dist_second;
		if (angle == game->player.point_of_view) {
			//printf("fin: %d\n", game->player.projection_plane.distances[i]);

		}
		i++;
		//printf("%i\n", dist);
		angle += game->player.projection_plane.angle_between_col;
	}
	//ver_dist = find_vertical_dist(game);
}