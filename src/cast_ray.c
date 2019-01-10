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


t_coordinates	find_horizontal_dist(t_game game, int sign_x, double angle)
{
	double				length;
	int					y_pos;
	int					i;
	int					sign_y;
	int					player_x;
	t_coordinates		intersaption;

	intersaption.x = 0;
	intersaption.y = 0;
	player_x = game.player.position.x;
	i = 0;
	sign_y = get_sign(angle);
	y_pos = BLOCK * i * sign_y * tan(angle * RADIAN);
	if (sign_y > 0)
		player_x--;
	while (game.map[(game.player.position.y + y_pos) / BLOCK][(player_x + BLOCK * sign_x * i) / BLOCK] != '#')
	{
		y_pos = (BLOCK * i * (-sign_x) * tan(angle * RADIAN));
		printf("angle: %f\n", angle);
		printf("sign_y %i\n", sign_y);
		printf("sign_x %i\n", sign_x);
		printf("tan: %f\n", tan(angle * RADIAN));
		printf("x: %i\n", (player_x + BLOCK * (sign_x) * i) / BLOCK);
		printf("y: %i\n", (game.player.position.y + y_pos) / BLOCK);
		printf("x_full: %i\n", (player_x + BLOCK * (sign_x) * i));
		printf("y_full: %i\n", (game.player.position.y + y_pos));
		i++;
	}
	length = BLOCK / cos(angle * RADIAN);
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
	int					sign;
	double				angle;
	//t_coordinates		ver_dist;

	angle = get_angle(game.player.point_of_view, &sign);
	hor_dist = find_horizontal_dist(game, sign, angle);
	//ver_dist = find_vertical_dist(game);
}