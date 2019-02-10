#include "wolf.h"

/*
**		set info about projection plane
*/

static t_projection_plane	set_projection_plane(float point_of_view)
{
	t_projection_plane	pp;

	pp.dist_to_pp = (PP_WIDTH / 2) / tan(PI * PP_FIELD / 360);
	pp.angle_between_col = (float)PP_FIELD / (float)PP_WIDTH;
	pp.left_angle = point_of_view + (PP_FIELD / 2);
	pp.right_angle = point_of_view - (PP_FIELD / 2);
	pp.distances = (float *)malloc(sizeof(float) * PP_WIDTH + 1);
	return (pp);
}	

/*
**		set info about player
*/

t_player			set_players_info(t_coordinates	players_position)
{
	t_player	player;

	player.position.x = players_position.x * BLOCK;
	player.position.y = players_position.y * BLOCK;
	player.size = 3;
	player.point_of_view = 90;
	player.projection_plane = set_projection_plane(player.point_of_view);
	return (player);
}