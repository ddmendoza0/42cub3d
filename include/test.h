/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:00:36 by diespino          #+#    #+#             */
/*   Updated: 2026/01/16 20:36:09 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define PI 3.14159265358979323846
# define DEBUG 0

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
	double	angle;
//	char	orientation;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	char		**map;
}	t_game;

/*typedef struct s_game
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
int		calculate_map_width(t_game *game);
int		validate_map_characters(t_game *game);
int		validate_map_closed(t_game *game);
void	free_game(t_game *game);*/
//void	move_player(mlx_t *mlx, t_player *player);

bool    touch(double ray_x, double ray_y, t_game *game);
void	move_player(t_game *game, t_player *player);
void	init_player(t_player *player);

#endif
