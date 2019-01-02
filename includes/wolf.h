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

# define WIDTH 1280
# define HEIGHT 1000

typedef	struct		s_coordinates
{
	int				x;
	int				y;
}					t_coordinates;

typedef	struct		s_object
{
	t_coordinates	coordinates[5];
}					t_object;

typedef	struct		s_window
{
	SDL_Window		*screen;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Texture 	*texture;
	Uint32 			*pixels;
}					t_window;

typedef	struct		s_game
{
	t_object		objects[5];
	t_coordinates	player;
	t_window		window;

	char			**map;
}					t_game;

t_game				create_map(int fd);
void				error_message(const char *error_message);
int					validate_line(char *map_string, int player);
void		 		find_player(char *map_line, t_coordinates *player, int y);
t_window	 		create_screen();
int					check_action(t_game game);
void				key_pressed(SDL_KeyboardEvent key, t_game game);

#endif