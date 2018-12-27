#include "wolf.h"


void	free_game(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i]) 
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

/*
**		get list size
*/

int		list_size(t_list *rows)
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
**		create copy map from list
*/

char**	check_list_and_create_map(t_list *rows)
{
	char	**map;
	int		size_of_list;
	int		i;

	i = 0;
	map = NULL;
	size_of_list = list_size(rows);
	map = (char **)malloc(sizeof(char *) * (size_of_list + 1));
	while(rows)
	{
		map[i] = ft_strdup(rows->content);
		free(rows->content);
		free(rows);
		rows = rows->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

/*
**		create map
*/

char**	create_map(int fd) 
{
	char 	*readen_line;
	char	**map = NULL;
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

	map = check_list_and_create_map(rows);
	return (map);
}

int		main(int ac, char **argv)
{
	int		fd;
	t_game	game;

	if (ac != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	game.map = create_map(fd);
	//free_game(&game);
	system("leaks wolf3d");
	return 0;
}