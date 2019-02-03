#include "wolf.h"

/*
**		error message
*/

void		error_message(const char *error_message)
{
	ft_printf("%s\n", error_message);
	exit(1);
}

/*
**		get list size
*/

static	int		list_size(t_list *rows)
{
	int num_of_cells;

	num_of_cells = 0;
	while (rows)
	{
		num_of_cells++;
		rows = rows->next;
	}
	return (num_of_cells);
}

/*
**		create and copy map from list
*/

static	t_game	check_list_and_create_map(t_list *rows)
{
	t_game			game;
	int				size_of_list;
	int				i;
	int				closed;

	i = 0;
	closed = 0;
	game.player.position.x = -1;
	size_of_list = list_size(rows);
	game.map = (char **)malloc(sizeof(char *) * (size_of_list + 1));
	while(rows)
	{
		find_player(rows->content, &game.player.position, i);
		closed = validate_line(rows->content, game.player.position.x);
		game.map[i] = ft_strdup(rows->content);
		// free(rows->content);
		// free(rows);
		rows = rows->next;
		i++;
	}
	game.map_size.y = i;
	game.map_size.x = ft_strlen(game.map[0]);
	game.map[i] = NULL;
	if (!closed)
		error_message("Didnt close");
	game.player = set_players_info(game.player.position);
	return (game);
}

/*
**		create map
*/

t_game		create_map(int fd)
{
	char 	*readen_line;
	t_game	game;
	t_list	*list;
	t_list	*rows;

	rows = NULL;
	while (get_next_line(fd, &readen_line))
	{
		list = malloc(sizeof(t_list));
		list->next = 0;
		list->content_size = ft_strlen(readen_line);
		list->content = ft_strdup(readen_line);
		ft_lstaddlast(&rows, list);
		ft_strdel(&readen_line);
	}
	game = check_list_and_create_map(rows);
	if (game.player.position.x == -1)
		error_message("No Player");
	return (game);
}