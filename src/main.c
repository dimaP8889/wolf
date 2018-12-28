#include "wolf.h"

/*
**		main
*/

int		main(int ac, char **argv)
{
	int		fd;
	t_game	game;

	if (ac != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	game = create_map(fd);
	system("leaks wolf3d");
	return 0;
}