#include "wolf.h"

/*
**		find horizontal distances
*/

void				set_intersections(t_ray_intersection* intersection_vert, t_ray_intersection* intersection_hor)
{
	intersection_vert->coord.x = -1;
	intersection_vert->coord.y = -1;
	intersection_vert->distance = -1;

	intersection_hor->coord.x = -1;
	intersection_hor->coord.y = -1;
	intersection_hor->distance = -1;
}

double 				shortest_dist(t_ray_intersection intersection_vert, t_ray_intersection intersection_hor)
{
	if (intersection_hor.distance == -1)
		return (intersection_vert.distance);
	if (intersection_vert.distance == -1)
		return (intersection_hor.distance);
	return (intersection_hor.distance > intersection_vert.distance ? intersection_vert.distance : intersection_hor.distance);
}

void 				get_one_step_coordinate(t_game *game, t_ray_intersection intersection)
{
	game->player.delta.x = (double)(intersection.coord.x - game->player.position.x) / (double)intersection.distance;
	game->player.delta.y = (double)(intersection.coord.y - game->player.position.y) / (double)intersection.distance;
}

t_coordinates		get_shortest_coord(t_ray_intersection intersection_vert, t_ray_intersection intersection_hor, t_game *game)
{
	t_ray_intersection		right_inter;

	if (intersection_hor.distance == -1)
		right_inter = intersection_vert;
	else if (intersection_vert.distance == -1)
		right_inter = intersection_hor;
	else 
		right_inter = intersection_hor.distance > intersection_vert.distance ? intersection_vert : intersection_hor;
	get_one_step_coordinate(game, right_inter);
	return (right_inter.coord);
}

void				find_horizontal_dist(t_game *game, double angle, t_ray_intersection *intersection)
{
	t_deltas		player;
	float			x_delta;
	float			y_delta;
	int				sign;

	sign = 1;
	player.x = (int)game->player.position.x;
	player.y = (int)game->player.position.y;
	if (angle >= 90 && angle < 270)
	{
		intersection->coord.x = (player.x / BLOCK) * BLOCK - 1;
		x_delta = -BLOCK;
	} else {
		sign = -1;
		intersection->coord.x = (player.x / BLOCK) * BLOCK + 64;
		x_delta = BLOCK;
	}
	intersection->coord.y = player.y + (player.x - intersection->coord.x) * tan(angle * RADIAN);
	y_delta = BLOCK * tan(angle * RADIAN);
	if (intersection->coord.y / 64 >= game->map_size.y || intersection->coord.y < 0) // check if out of range
		return ;
	while (game->map[(int)intersection->coord.y / BLOCK][(int)intersection->coord.x / BLOCK] != '#')
	{
		intersection->coord.x += x_delta;
		intersection->coord.y += y_delta * sign;
		if (intersection->coord.y / 64 >= game->map_size.y || intersection->coord.y < 0) // check if out of range
			return ;
	}
	intersection->distance = sqrt((player.x - intersection->coord.x) * (player.x - intersection->coord.x) + (player.y - intersection->coord.y) * (player.y - intersection->coord.y));
}

/*
**		find vertical distances
*/

void				find_vertical_dist(t_game *game, double angle, t_ray_intersection *intersection)
{
	t_deltas		player;
	float			x_delta;
	float			y_delta;
	int				sign;

	sign = 1;
	player.x = (int)game->player.position.x;
	player.y = (int)game->player.position.y;
	if (angle >= 0 && angle < 180)
	{
		intersection->coord.y = (player.y / BLOCK) * BLOCK - 1;
		y_delta = -BLOCK;
	}
	else if (angle >= 180 && angle < 360)
	{
		sign = -1;
		intersection->coord.y = (player.y / BLOCK) * BLOCK + 64;
		y_delta = BLOCK;
	}
	intersection->coord.x = player.x + (player.y - intersection->coord.y) / tan(angle * RADIAN);
	x_delta = BLOCK / tan(angle * RADIAN);
	if (intersection->coord.x / 64 >= game->map_size.x || intersection->coord.x < 0) // check if out of range
		return ;
	while (game->map[(int)intersection->coord.y / BLOCK][(int)intersection->coord.x / BLOCK] != '#')
	{
		intersection->coord.x += sign * x_delta;
		intersection->coord.y += y_delta;
		if (intersection->coord.x / 64 >= game->map_size.x || intersection->coord.x < 0) // check if out of range
			return ;
	}
	intersection->distance = sqrt((player.x - intersection->coord.x) * (player.x - intersection->coord.x) + (player.y - intersection->coord.y) * (player.y - intersection->coord.y));
}

/*
**		cast a ray to find distances to wall
*/

void	cast_ray(t_game *game)
{
	t_ray_intersection  intersection_vert;
	t_ray_intersection  intersection_hor;
	int					i;
	double				angle;
	
	i = 0;
	check_angles(game);
	angle = game->player.projection_plane.left_angle;
	while (i <= game->player.projection_plane.width)
	{
		set_intersections(&intersection_vert, &intersection_hor);
		check_angles(game);
		if (angle >= 360)
			angle = angle - 360;
		find_horizontal_dist(game, angle, &intersection_hor);
		find_vertical_dist(game, angle, &intersection_vert);
		game->player.projection_plane.distances[i] = shortest_dist(intersection_vert, intersection_hor);
		i++;
		//printf("%i\n", dist);
		angle += game->player.projection_plane.angle_between_col;
	}
	game->player.line = get_shortest_coord(intersection_vert, intersection_hor, game);
	//ver_dist = find_vertical_dist(game);
}