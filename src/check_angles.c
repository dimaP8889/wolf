#include "wolf.h"

double			find_angle(double	angle)
{
	if (angle >= 360)
		return (angle - 360);
	if (angle < 0)
		return 360 + angle;
	return angle;
}

void			check_angles(t_game *game)
{
	game->player.point_of_view = find_angle(game->player.point_of_view);
	game->player.projection_plane.left_angle = find_angle(game->player.projection_plane.left_angle);
	game->player.projection_plane.right_angle = find_angle(game->player.projection_plane.right_angle);
}
