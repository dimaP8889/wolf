#include "wolf.h"


void	free_game(t_game *game)
{
	free(game->player.projection_plane.distances);
}

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
	game.window = create_screen();
	//fill_pixels(&game);
	while (1)
	{
		if (!check_action(&game))
			break;
		draw(game);
	}
	// free_game(&game);
	printf("size : %i\n", game.player.size);
	printf("point of view : %f\n", game.player.point_of_view);
	printf("y : %f\n", game.player.position.y);
	printf("x : %f\n", game.player.position.x);
	printf("height pp : %i\n", PP_HEIGHT);
	printf("width pp : %i\n", PP_WIDTH);
	printf("field of view : %i\n", PP_FIELD);
	printf("dist to pp : %i\n", game.player.projection_plane.dist_to_pp);
	printf("angle between col : %f\n", game.player.projection_plane.angle_between_col);
	printf("left angle : %f\n", game.player.projection_plane.left_angle);
	printf("right angle : %f\n", game.player.projection_plane.right_angle);
	SDL_DestroyWindow(game.window.window);
	//SDL_Quit();
	system("leaks wolf3d");
	return 0;
}