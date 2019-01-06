#include "wolf.h"

t_coordinates	find_horizontal_dist(t_game game)
{
	t_coordinates		intersaption;

	if (game.player.point_of_view >= 0 && game.player.point_of_view < 180)
	{
		intersaption.y = game.player.position.y / 64 * game.block_size - 1;
	} else if (game.player.point_of_view >= 180 && game.player.point_of_view < 360)
	{
		intersaption.y = game.player.position.y / 64 * game.block_size + 64;
	}
	intersaption.x = game.player.position.x + (game.player.position.y - intersaption.y) / tan(game.player.point_of_view * PI / 360 
		+ 0 * game.player.projection_plane.angle_between_col);
	if (game.map[intersaption.y / 64][intersaption.x / 64])
		return (intersaption)
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
	printf("%i\n", hor_dist.x);
	printf("%i\n", hor_dist.y);
	//ver_dist = find_vertical_dist(game);
}