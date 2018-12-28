#ifndef WOLF_H
# define WOLF_H
# include "libft.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL.h"
# include <math.h>
# include <fcntl.h>
# include <time.h>

typedef	struct		s_coordinates
{
	int				x;
	int				y;
}					t_coordinates;

typedef	struct		s_object
{
	t_coordinates	coordinates[5];
}					t_object;

typedef	struct		s_game
{
	t_object		objects[5];
	t_coordinates	player;
	char			**map;
}					t_game;

t_game				create_map(int fd);
void				error_message(char *error_message);
int					validate_line(char *map_string, int player);
void		 		find_player(char *map_line, t_coordinates *player, int y);

#endif