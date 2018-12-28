#include "wolf.h"

/*
**		find first position of sharp
*/

static	int		find_first_position_of_piece(char *map_string, char piece)
{
	int		i;

	i = 0;
	while (map_string[i])
	{
		if (map_string[i] == piece)
			return (i);
		i++;
	}
	return (-1);
}

/*
**		find last position of sharp
*/

static	int		find_last_position_of_piece(char *map_string, char piece)
{
	int		i;
	int		position;

	i = 0;
	position = -1;
	while (map_string[i])
	{
		if (map_string[i] == piece)
			position = i;
		i++;
	}
	return (position);
}

/*
**		check if line is closed
*/

static	int		check_closed(int first_x, int last_x, char *map_line, char piece)
{
	int		i;

	i = first_x;
	while (i < last_x)
	{
		if (map_line[i] != piece)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/*
**		validate map line
*/

int				validate_line(char *map_string, int player)
{
	static int	prev_first_x;
	static int	prev_last_x;
	int			first_x;
	int			last_x;

	if (player != -1 && (player < prev_first_x || player > prev_last_x))
		error_message("Wrong player position");
	if (ft_strchr(map_string, '#'))
	{
		first_x = find_first_position_of_piece(map_string, '#');
		last_x = find_last_position_of_piece(map_string, '#');
		if (!prev_last_x && !prev_first_x)
		{
			prev_last_x = last_x;
			prev_first_x = first_x;
			if (!check_closed(first_x, last_x, map_string, '#'))
				error_message("Your first line is not closed");
		} else if (prev_last_x != last_x || prev_first_x != first_x) {
			error_message("Not good line");
		} else {
			return (check_closed(first_x, last_x, map_string, '#'));
		}
	}
	return (0);
}