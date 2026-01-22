/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:26:35 by diespino          #+#    #+#             */
/*   Updated: 2026/01/20 18:26:45 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	draw_col(double dist, int color, int screen_x, t_game *game)
{
	double	dist_plane;
	double	height;
	int	start_y;
	int	end_y;

	dist_plane = (WIDTH / 2.0) / tan(PI / 6.0);
	height = (BLOCK / dist) * dist_plane;
	start_y = (int)((HEIGHT - height) / 2.0);
	end_y = (int)(start_y + height);
	if (start_y < 0)
		start_y = 0;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	while (start_y < end_y)
	{
		pixel_put(game, screen_x, start_y, color);
		start_y++;
	}
}*/
void	draw_col(double dist, int screen_x, int side, double wall_x, t_game* game)
{
	mlx_texture_t	*texture;
	double			dist_plane;
	double			height;
	int				start_y;
	int				end_y;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	uint32_t		color;
	int				y;


	if (side == 0)
	{
		if (game->rcast.ray_x > 0)
			texture = game->tex_east;
		else
			texture = game->tex_west;
	}
	else
	{
		if (game->rcast.ray_y > 0)
			texture = game->tex_south;
		else
			texture = game->tex_north;
	}
	dist_plane = (WIDTH / 2.0) / tan(PI / 6.0);
	height = (BLOCK / dist) * dist_plane;
	start_y = (int)((HEIGHT - height) / 2.0);
	end_y = (int)(start_y + height);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((side == 0 && game->rcast.ray_x < 0) || (side == 1 && game->rcast.ray_y < 0))
		tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / height;
	tex_pos = (start_y - HEIGHT / 2.0 + height / 2.0) * step;
	if (start_y < 0)
		y = 0;
	else
		y = start_y;
	if (start_y < 0)
		tex_pos += (-start_y) * step;
	while (y < end_y && y < HEIGHT)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = ((uint32_t *)texture->pixels)[tex_y * texture->width + tex_x];
		pixel_put(game, screen_x, y, color);
		y++;
	}
}

/*static int	get_wall_text(t_game* game, int side)
{
	if(side == 0)
	{
		if (game->rcast.ray_x > 0)
			return (0x0000FFFF);// EAST [BLUE];
		else
			return (0xFF0000FF);// WEST [RED]
	}
	else
	{
		if (game->rcast.ray_y > 0)
			return (0x00FFFFFF);// SOUTH [LIGTH BLUE]
		else
			return (0x00FF00FF);// NORTH [GREEN]
	}
}*/

double	grid_dist(t_game *game, int side, double ray_angle)
{
	double	dist;
	
	if (side == 0)
		dist = ((game->rcast.map_x - game->player.x / BLOCK
			+ (1 - game->rcast.step_x) / 2.0)
				* BLOCK / game->rcast.ray_x);
	else
		dist = ((game->rcast.map_y - game->player.y / BLOCK
			+ (1 - game->rcast.step_y) / 2.0)
				* BLOCK / game->rcast.ray_y);
	dist *= cos(ray_angle - game->player.angle);
	return (dist);
}

// Falta DEBUG --> pixel_put(game, (int)ray_x, (int)ray_y, 0xFF0000FF);
static int	grid_move(t_game *game)
{
	bool	hit;
	int		side;
	
	hit = false;
	while(!hit)
	{
		if (game->rcast.side_dist_x < game->rcast.side_dist_y)
		{
			game->rcast.side_dist_x += game->rcast.dist_x;
			game->rcast.map_x += game->rcast.step_x;
			side = 0;
		}
		else
		{
			game->rcast.side_dist_y += game->rcast.dist_y;
			game->rcast.map_y += game->rcast.step_y;
			side = 1;
		}
		if (game->map.grid[game->rcast.map_y][game->rcast.map_x] == '1')
			hit = true;
	}
	return (side);
}

static void	grid_pos_init(t_game *game)
{
	if (game->rcast.ray_x < 0)
	{
		game->rcast.step_x = -1;
		game->rcast.side_dist_x = (game->player.x - game->rcast.map_x
			* BLOCK) / fabs(game->rcast.ray_x);
	}
	else
	{
		game->rcast.step_x = 1;
		game->rcast.side_dist_x = ((game->rcast.map_x + 1)
			* BLOCK - game->player.x) / fabs(game->rcast.ray_x);
	}
	if (game->rcast.ray_y < 0)
	{
		game->rcast.step_y = -1;
		game->rcast.side_dist_y = (game->player.y - game->rcast.map_y
			* BLOCK) / fabs(game->rcast.ray_y);
	}
	else
	{
		game->rcast.step_y = 1;
		game->rcast.side_dist_y = ((game->rcast.map_y + 1)
			* BLOCK - game->player.y) / fabs(game->rcast.ray_y);
	}
}

/*void	draw_line(t_game* game, double ray_angle, int screen_x)
{
	int		side;
	int		color;
	double	dist;

	game->rcast.map_x = (int)(game->player.x / BLOCK);
	game->rcast.map_y = (int)(game->player.y/ BLOCK);
	game->rcast.ray_x = cos(ray_angle);
	game->rcast.ray_y = sin(ray_angle);
	game->rcast.dist_x = fabs(BLOCK / game->rcast.ray_x);
	game->rcast.dist_y = fabs(BLOCK / game->rcast.ray_y);
//	Caculo de primera intersecciones de la grid
	grid_pos_init(game);
//	Movimiento en grid hasta pared
	side = grid_move(game);
//	distancia perfecta al muro y sin ojo de pez
	dist = grid_dist(game, side, ray_angle);
//	colore pared
	color = get_wall_text(game, side);
//	dibujo de columnas
	draw_col(dist, color, screen_x, game);
}*/
void	draw_line(t_game *game, double ray_angle, int screen_x)
{
	int		side;
	double	dist;
	double	wall_x;

	game->rcast.map_x = (int)(game->player.x / BLOCK);
	game->rcast.map_y = (int)(game->player.y / BLOCK);
	game->rcast.ray_x = cos(ray_angle);
	game->rcast.ray_y = sin(ray_angle);
	game->rcast.dist_x = fabs(BLOCK / game->rcast.ray_x);
	game->rcast.dist_y = fabs(BLOCK / game->rcast.ray_y);
	grid_pos_init(game);
	side = grid_move(game);
	dist = grid_dist(game, side, ray_angle);
	if (side == 0)
		wall_x = game->player.y + dist * game->rcast.ray_y;
	else
		wall_x = game->player.x + dist * game->rcast.ray_x;
	wall_x = wall_x / BLOCK;
	wall_x -= floor(wall_x);
	draw_col(dist, screen_x, side, wall_x, game);
}
