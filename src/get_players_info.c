#include "wolf.h"

/*
**		set info about projection plane
*/

static t_projection_plane	set_projection_plane(double point_of_view)
{
	t_projection_plane	pp;

	pp.height = 200;
	pp.width = 320;
	pp.field_of_view = 60;
	pp.dist_to_pp = (pp.width / 2) / tan(PI * pp.field_of_view / 360);
	pp.angle_between_col = pp.field_of_view / pp.width;
	pp.left_angle = point_of_view - (pp.field_of_view / 2);
	pp.right_angle = point_of_view + (pp.field_of_view / 2);
	return (pp);
}	

/*
**		set info about player
*/

t_player			set_players_info(t_coordinates	players_position)
{
	t_player	player;

	player.position = players_position;
	player.size = 3;
	player.move_speed = 1;
	player.point_of_view = 0;
	player.projection_plane = set_projection_plane(player.point_of_view);
	return (player);
}