#include "wolf.h"

/*
**		set info about projection plane
*/

static t_projection_plane	set_projection_plane(double point_of_view)
{
	t_projection_plane	pp;

	pp.dist_to_pp = (PP_WIDTH / 2) / tan(PI * PP_FIELD / 360);
	pp.angle_between_col = (double)PP_FIELD / (double)PP_WIDTH;
	pp.left_angle = point_of_view + (PP_FIELD / 2);
	pp.right_angle = point_of_view - (PP_FIELD / 2);
	pp.distances = (int*)malloc(sizeof(int) * PP_WIDTH);
	return (pp);
}	

/*
**		set info about player
*/

t_player			set_players_info(t_coordinates	players_position)
{
	t_player	player;

	player.line.x= -1; // need to delete after
	player.line.y = -1; // need to delete after
	player.position.x = players_position.x * BLOCK;
	player.position.y = players_position.y * BLOCK;
	player.size = 3;
	player.point_of_view = 90;
	player.projection_plane = set_projection_plane(player.point_of_view);
	return (player);
}