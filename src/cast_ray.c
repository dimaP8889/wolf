#include "wolf.h"

int				get_i(double angle, int i)
{
	if (angle > 180)
		return (i + 1);
	return (i - 1);
}

double			get_angle(double cur_angle)
{
	if (cur_angle > 90 && cur_angle <= 180)
		return cur_angle - 90;
	else if (cur_angle > 180 && cur_angle <= 270)
		return cur_angle - 180;
	else if (cur_angle > 270 && cur_angle <= 360)
		return cur_angle - 270;
	return cur_angle;
}


t_coordinates	find_horizontal_dist(t_game game)
{
	double				length;
	int					x_pos;
	double				angle;
	int					i;
	t_coordinates		intersaption;

	intersaption.x = 0;
	intersaption.y = 0;
	i = 0;
	angle = get_angle(game.player.point_of_view);
	//printf("%i\n", i);
	if (angle < 45)
	{
		x_pos = BLOCK * i / tan(angle * RADIAN);
		while (game.map[(game.player.position.y + BLOCK * i) / BLOCK][(game.player.position.x + x_pos) / BLOCK] != '#')
		{
			x_pos = (BLOCK / tan(angle * RADIAN)) * i;
			i = get_i(game.player.point_of_view, i);
		}
		length = BLOCK / sin(angle * RADIAN);
	} else {
		x_pos = BLOCK * i * tan(angle * RADIAN);
		while (game.map[(game.player.position.y + BLOCK * i) / BLOCK][(game.player.position.x + x_pos) / BLOCK] != '#')
		{
			x_pos = BLOCK * i * tan(angle * RADIAN);
			i = get_i(game.player.point_of_view, i);
		}
		length = BLOCK / cos(angle * RADIAN);
	}
	printf("%f\n", length);
	// i = 0;
	// if (game.player.point_of_view >= 0 && game.player.point_of_view < 180)
	// {
	// 	intersaption.y = (game.player.position.y / BLOCK) * BLOCK - 1; // find y where ray can touch wall
	// } else if (game.player.point_of_view >= 180 && game.player.point_of_view < 360)
	// {
	// 	intersaption.y = (game.player.position.y / BLOCK) * BLOCK + 64;
	// }
	// intersaption.x = -64;

	// printf("%c\n", game.map[intersaption.y / 64][intersaption.x / 64]);
	// while (game.map[intersaption.y / 64][intersaption.x / 64] != '#')
	// {
	// 	printf("x: %i\n", intersaption.x);
	// 	printf("y: %i\n", intersaption.y);
	// 	if (game.player.point_of_view >= 0 && game.player.point_of_view < 180)
	// 	{
	// 		intersaption.y -= 64; // find y where ray can touch wall
	// 	} else if (game.player.point_of_view >= 180 && game.player.point_of_view < 360)
	// 	{
	// 		intersaption.y += 64;
	// 	}
	// 	intersaption.x = game.player.position.x + (game.player.position.y - intersaption.y) / tan(game.player.point_of_view * PI / 360);
	// 	i++;
	//}
	return(intersaption);
}

/*
**		cast a ray to find distances to wall
*/

void	cast_ray(t_game game)
{
	t_coordinates		hor_dist;
	//t_coordinates		ver_dist;


	hor_dist = find_horizontal_dist(game);
	//ver_dist = find_vertical_dist(game);
}