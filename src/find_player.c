#include "wolf.h"

/*
**		looking for player
*/

void		 find_player(char *map_line, t_coordinates *player, int y)
{
	char	*founded_position;
	int		new_x;

	new_x = 0;
	founded_position = ft_strchr(map_line, '*');
	if (founded_position)
	{
		new_x = founded_position - map_line;
		if (player->x != -1)
			error_message("Already got player");
		player->x = new_x;
		player->y = y;
	}
}