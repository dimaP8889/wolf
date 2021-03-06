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

# define				MOVE 12
# define				TURN 30
# define 				WIDTH 960
# define 				HEIGHT 800
# define				PI 3.14159265358979323846
# define				BLOCK 64
# define				RADIAN PI / 180
# define				PP_WIDTH 960
# define				PP_HEIGHT 800
# define				PP_FIELD 60

typedef	struct			s_coordinates
{
	float				x;
	float				y;
}						t_coordinates;

typedef	struct			s_draw_params
{
	float				*heights;
	float 				*positions;
}						t_draw_params;

typedef	struct			s_deltas
{
	int					x;
	int					y;
}						t_deltas;

typedef struct 			s_ray_intersection 
{
	t_coordinates		coord;
	float				distance;
}						t_ray_intersection;

typedef	struct			s_projection_plane
{
	int					dist_to_pp;
	float				*distances;
	float				angle_between_col;
	float				left_angle;
	float				right_angle;
}						t_projection_plane;

typedef	struct			s_player
{
	t_coordinates		position;
	t_coordinates		line;
	t_coordinates		delta;
	t_projection_plane	projection_plane;
	int					size;
	float				point_of_view;
}						t_player;

typedef	struct			s_object
{
	t_coordinates		coordinates[5];
}						t_object;

typedef	struct			s_window
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture 		*texture;
	Uint32 				*pixels;
}						t_window;

typedef	struct			s_game
{
	t_object			objects[5];
	t_player			player;
	t_window			window;
	char				**map;
	t_coordinates		map_size;
}						t_game;

t_game					create_map(int fd);
void					error_message(const char *error_message);
int						validate_line(char *map_string, int player);
void		 			find_player(char *map_line, t_coordinates *player, int y);
t_window	 			create_screen();
int						check_action(t_game *game);
void					key_pressed(SDL_KeyboardEvent key, t_game *game);
void					draw(t_game game);
t_player				set_players_info(t_coordinates	players_position);
void					fill_pixels(t_game *game, t_draw_params draw_params);
void					cast_ray(t_game *game);
void					check_angles(t_game *game);

#endif