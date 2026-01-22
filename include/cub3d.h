

#ifndef CUB3D_H
# define CUB3D_H

// --- CONSTANTS ---

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64
# define PI 3.14159265359


// --- LIBRARIES ---

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>


// --- STRUCTURES ---

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int	floor_r;
	int	floor_g;
	int	floor_b;
	int	ceiling_r;
	int	ceiling_g;
	int	ceiling_b;
}	t_colors;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	char	orientation;
	double	angle;
}	t_player;

typedef struct s_game
{
	t_textures	textures;
	t_colors	colors;
	t_map		map;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			has_north;
	int			has_south;
	int			has_west;
	int			has_east;
	int			has_floor;
	int			has_ceiling;
}	t_game;


// --- DEFINITIONS ---

int		main(int argc, char **argv);
int		parse_cub_file(char *filename, t_game *game);
int		parse_identifier(char *line, t_game *game);
int		validate_identifiers(t_game *game);
int		parse_map(int fd, t_game *game);
int		calculate_map_width(t_game *game);
int		validate_map_characters(t_game *game);
int		validate_map_closed(t_game *game);
void	free_game(t_game *game);
int		init_game(t_game *game);
void	draw_loop(void *param);
void	move_player(t_game *game, t_player *player);
void	draw_line(t_game *game, double ray_angle, int screen_x);
void	pixel_put(t_game *game, int x, int y, uint32_t color);
void	clear_img(t_game *game);

#endif