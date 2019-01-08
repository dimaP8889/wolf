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

# define 				WIDTH 1000
# define 				HEIGHT 800
# define				PI 3.14159265358979323846
# define				BLOCK 64
# define				RADIAN PI / 360

typedef	struct			s_coordinates
{
	int					x;
	int					y;
}						t_coordinates;

typedef	struct			s_projection_plane
{
	int					height;
	int					width;
	int					field_of_view;
	int					dist_to_pp;
	int					*distances;
	double				angle_between_col;
	double				left_angle;
	double				right_angle;
}						t_projection_plane;

typedef	struct			s_player
{
	t_coordinates		position;
	t_projection_plane	projection_plane;
	int					size;
	double				move_speed;
	double				point_of_view;
}						t_player;

typedef	struct			s_object
{
	t_coordinates		coordinates[5];
}						t_object;

typedef	struct			s_window
{
	SDL_Window			*window;
	SDL_Event			event;
	SDL_Renderer		*renderer;
	SDL_Texture 		*texture;
	Uint32 				*pixels;
}						t_window;

typedef	struct			s_game
{
	t_object			objects[5];
	t_player			player;
	t_window			window;
	int					block_size;
	char				**map;
}						t_game;

t_game					create_map(int fd);
void					error_message(const char *error_message);
int						validate_line(char *map_string, int player);
void		 			find_player(char *map_line, t_coordinates *player, int y);
t_window	 			create_screen();
int						check_action(t_game game);
void					key_pressed(SDL_KeyboardEvent key, t_game game);
void					draw(t_game game);
t_player				set_players_info(t_coordinates	players_position);
void					fill_pixels(t_game game);
void					cast_ray(t_game game);

#endif