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
	char			**map;
}					t_game;

#endif