

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

// Estructuras básicas para empezar
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
}	t_player;

typedef struct s_game
{
	t_textures	textures;
	t_colors	colors;
	t_map		map;
	t_player	player;
	mlx_t		*mlx;
	int			has_north;
	int			has_south;
	int			has_west;
	int			has_east;
	int			has_floor;
	int			has_ceiling;
}	t_game;

//DEFINITIONS
int		main(int argc, char **argv);
int		parse_cub_file(char *filename, t_game *game);
int		parse_identifier(char *line, t_game *game);
int		validate_identifiers(t_game *game);
int		parse_map(int fd, t_game *game);

#endif