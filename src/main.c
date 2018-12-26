#include "wolf.h"

/*
**		check input params
*/

void	check_input(int fd) 
{
	ft_printf("%i\n", fd);
}

int		main(int ac, char **argv)
{
	int fd;

	if (ac != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	check_input(fd);
	return 0;
}