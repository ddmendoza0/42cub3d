/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:11:03 by diespino          #+#    #+#             */
/*   Updated: 2026/04/10 13:20:49 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// --- CONSTANTS ---

# define WIDTH 1920
# define HEIGHT 1080
# define BLOCK 64
# define PI 3.14159265359
# define MOUSE_SENS 0.005

//minimap
# define MINIMAP_PADDING 20
# define MM_RADIUS 100
# define MM_SCALE 12

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
	char	*door;
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

typedef struct s_texdata
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
}	t_texdata;

typedef struct s_col
{
	double	dist;
	double	wall_x;
	int		screen_x;
	int		side;
	char	block;
}	t_col;

typedef struct s_proj
{
	double	height;
	int		start_y;
	int		end_y;
	int		side;
}	t_proj;

typedef struct s_player
{
	double	x;
	double	y;
	char	orientation;
	double	angle;
}	t_player;

typedef struct s_rcast
{
	int		map_x;
	int		map_y;
	double	ray_x;
	double	ray_y;
	double	side_dist_x;
	double	side_dist_y;
	double	dist_x;
	double	dist_y;
	int		step_x;
	int		step_y;
}	t_rcast;

typedef struct s_mmpos
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
}	t_mmpos;

typedef struct s_game
{
	t_textures		textures;
	t_colors		colors;
	t_map			map;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_rcast			rcast;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_east;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_door;
	int				has_north;
	int				has_south;
	int				has_west;
	int				has_east;
	int				has_floor;
	int				has_ceiling;
	int				has_door;
}	t_game;

// --- DEFINITIONS ---

int		main(int argc, char **argv);
int		parse_cub_file(char *filename, t_game *game);
int		parse_identifier(char *line, t_game *game);
int		parse_color(char *line, t_colors *colors, int is_floor);
int		normalize_map(t_game *game);
int		validate_identifiers(t_game *game);
int		parse_map(int fd, t_game *game, char *first_line);
int		is_valid_char(char c);
int		is_player(char c);
int		validate_texture_file(char *path);
int		validate_map_characters(t_game *game);
char	**convert_list_to_array(t_list *map_lines, int height);
int		validate_map_data(t_game *game);
int		validate_map_closed(t_game *game);
int		validate_rgb_count(char **rgb);
int		validate_rgb_range(char **rgb, int *r, int *g, int *b);
void	free_rgb_array(char **rgb);
void	free_game(t_game *game);
int		init_game(t_game *game);
void	draw_loop(void *param);
void	draw_minimap(t_game *game);
void	move_player(t_game *game, t_player *player);
void	draw_col(t_col *col, t_game *game);
void	draw_line(t_game *game, double ray_angle, int screen_x);
void	pixel_put(t_game *game, int x, int y, uint32_t color);
void	clear_img(t_game *game);
int		load_textures(t_game *game);
void	key_callback(mlx_key_data_t keydata, void *param);

#endif
