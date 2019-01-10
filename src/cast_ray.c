#include "wolf.h"

int				get_i(double angle, int i)
{
	if (angle > 180)
		return (i + 1);
	return (i - 1);
}

double			get_angle(double cur_angle, int *sign)
{
	if (cur_angle >= 135 && cur_angle < 315)
	{
		*sign = -1;
		if (cur_angle - 180 < 0)
			return 180 + cur_angle;
		return cur_angle - 180;
	}
	*sign = 1;
	return cur_angle;
}

int				get_sign(double angle)
{
	if (angle >= 315)
		return -1;
	return 1;
}

t_coordinates	find_horizontal_dist(t_game game, double angle)
{
	t_coordinates	A;
	t_coordinates	player;
	int				x_delta;
	int				y_delta;

	player.x = game.player.position.x;
	player.y = game.player.position.y;
	if (angle >= 90 && angle < 270)
	{
		A.x = (player.x / BLOCK) * BLOCK - 1;
		x_delta = -BLOCK;
	} else {
		A.x = (player.x / BLOCK) * BLOCK + BLOCK;
		x_delta = BLOCK;
	}
	A.y = player.y + (player.x - A.x) * tan(angle * RADIAN);
	y_delta = BLOCK * tan(angle * RADIAN);
	while (game.map[A.y / BLOCK][A.x / BLOCK] != '#')
	{
		A.x += x_delta;
		A.y += y_delta;
	}
	printf("x: %i\n", A.x);
	printf("y: %i\n", A.y);
	return (player);
}

t_coordinates	find_vertical_dist(t_game game, double angle)
{
	t_coordinates	A;
	t_coordinates	player;
	int				x_delta;
	int				y_delta;

	player.x = game.player.position.x;
	player.y = game.player.position.y;
	if (angle >= 0 && angle < 180)
	{
		A.y = (player.y / BLOCK) * BLOCK - 1;
		y_delta = -BLOCK;
	}
	else if (angle >= 180 && angle < 360)
	{
		A.y = (player.y / BLOCK) * BLOCK + BLOCK;
		y_delta = BLOCK;
	}
	A.x = player.x + (player.y - A.y) / tan(angle * RADIAN);
	x_delta = BLOCK / tan(angle * RADIAN);
	while (game.map[A.y / BLOCK][A.x / BLOCK] != '#')
	{
		A.x += x_delta;
		A.y += y_delta;
	}
	printf("x: %i\n", A.x);
	printf("y: %i\n", A.y);
	return (player);
}

/*
**		cast a ray to find distances to wall
*/

void	cast_ray(t_game game)
{
	t_coordinates		dist;
	//int					sign;
	//double				angle;
	double				angle;
	
	angle = game.player.point_of_view;
	//while (angle < game.player.projection_plane.right_angle)
	{
		//angle = get_angle(game.player.point_of_view, &sign);
		if ((angle >= 45 && angle <= 135) || (angle >= 225 && angle <= 315))
			dist = find_vertical_dist(game, angle);
		else if (angle > 315 || angle < 45 || (angle > 135 && angle < 225))
			dist = find_horizontal_dist(game, angle);
		angle += game.player.projection_plane.angle_between_col;
	}
	//ver_dist = find_vertical_dist(game);
}