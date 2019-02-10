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

float 				shortest_dist(t_ray_intersection intersection_vert, t_ray_intersection intersection_hor, float angle)
{

	float 	counted_angle;

	counted_angle = cos(angle * RADIAN);
	if (intersection_hor.distance == -1)
		return (intersection_vert.distance * counted_angle);
	if (intersection_vert.distance == -1)
		return (intersection_hor.distance * counted_angle);
	return (intersection_hor.distance > intersection_vert.distance ? intersection_vert.distance * counted_angle : intersection_hor.distance * counted_angle);
}

void 				get_one_step_coordinate(t_game *game, t_ray_intersection intersection)
{
	game->player.delta.x = (intersection.coord.x - game->player.position.x) / intersection.distance;
	game->player.delta.y = (intersection.coord.y - game->player.position.y) / intersection.distance;
}

void				find_one_step(t_ray_intersection intersection_vert, t_ray_intersection intersection_hor, t_game *game)
{
	t_ray_intersection		right_inter;

	if (intersection_hor.distance == -1)
		right_inter = intersection_vert;
	else if (intersection_vert.distance == -1)
		right_inter = intersection_hor;
	else 
		right_inter = intersection_hor.distance > intersection_vert.distance ? intersection_vert : intersection_hor;
	get_one_step_coordinate(game, right_inter);
}

void				find_horizontal_dist(t_game *game, float angle, t_ray_intersection *intersection)
{
	t_deltas		player;
	float			x_delta;
	float			y_delta;
	int				sign;

	sign = 1;
	player.x = (int)game->player.position.x;
	player.y = (int)game->player.position.y;
	if (angle >= 90 && angle <= 270)
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
	if (angle == game->player.point_of_view) {
			printf("y: %f\n", intersection->coord.y / BLOCK);
			printf("x: %f\n", intersection->coord.x / BLOCK);
		}
	while (game->map[(int)(intersection->coord.y / BLOCK)][(int)(intersection->coord.x / BLOCK)] != '#')
	{
		intersection->coord.x += x_delta;
		intersection->coord.y += y_delta * sign;
		if (intersection->coord.y / 64 >= game->map_size.y || intersection->coord.y <= 0) // check if out of range
			return ;
	}
	intersection->distance = sqrt((player.x - intersection->coord.x) * (player.x - intersection->coord.x) + (player.y - intersection->coord.y) * (player.y - intersection->coord.y));
}

/*
**		find vertical distances
*/

void				find_vertical_dist(t_game *game, float angle, t_ray_intersection *intersection)
{
	t_deltas		player;
	float			x_delta;
	float			y_delta;
	int				sign;

	sign = 1;
	player.x = (int)game->player.position.x;
	player.y = (int)game->player.position.y;
	if (angle >= 0 && angle <= 180)
	{
		intersection->coord.y = (player.y / BLOCK) * BLOCK - 1;
		y_delta = -BLOCK;
	}
	else {
		sign = -1;
		intersection->coord.y = (player.y / BLOCK) * BLOCK + 64;
		y_delta = BLOCK;
	}
	intersection->coord.x = player.x + (player.y - intersection->coord.y) / tan(angle * RADIAN);
	x_delta = BLOCK / tan(angle * RADIAN);
	if (intersection->coord.x / 64 >= game->map_size.x || intersection->coord.x < 0) // check if out of range
		return ;
	while (game->map[(int)(intersection->coord.y / BLOCK)][(int)(intersection->coord.x / BLOCK)] != '#')
	{
		intersection->coord.x += sign * x_delta;
		intersection->coord.y += y_delta;
		if (intersection->coord.x / 64 >= game->map_size.x || intersection->coord.x <= 0) // check if out of range
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
	float				angle;
	
	i = 0;
	check_angles(game);
	angle = game->player.projection_plane.left_angle;
	while (i < PP_WIDTH)
	{
		set_intersections(&intersection_vert, &intersection_hor);
		check_angles(game);
		if (angle >= 360)
			angle = angle - 360;
		find_horizontal_dist(game, angle, &intersection_hor);
		find_vertical_dist(game, angle, &intersection_vert);
		game->player.projection_plane.distances[i] = shortest_dist(intersection_vert, intersection_hor, fabs(PP_FIELD / 2 - i * game->player.projection_plane.angle_between_col));
		if (angle == game->player.point_of_view) {
			find_one_step(intersection_vert, intersection_hor, game);
			printf("vert_distance: %f\n", intersection_vert.distance);
			printf("hor_distance: %f\n", intersection_hor.distance);
			printf("distance: %f\n", game->player.projection_plane.distances[i]);
			printf("angle: %f\n\n", game->player.point_of_view);
		}
		i++;
		angle += game->player.projection_plane.angle_between_col;
	}
	game->player.projection_plane.distances[i] = 0;
	//game->player.line = get_shortest_coord(intersection_vert, intersection_hor, game);
	//ver_dist = find_vertical_dist(game);
}