/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:26:35 by diespino          #+#    #+#             */
/*   Updated: 2026/04/09 15:56:35 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	grid_dist(t_game *game, int side, double ray_angle)
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

static int	grid_move(t_game *game)
{
	bool	hit;
	int		side;

	hit = false;
	while (!hit)
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
		if (game->map.grid[game->rcast.map_y][game->rcast.map_x] == '1' ||
			game->map.grid[game->rcast.map_y][game->rcast.map_x] == 'D')
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

void	draw_line(t_game *game, double ray_angle, int screen_x)
{
	int		side;
	double	dist;
	double	wall_x;
	t_col	col;

	game->rcast.map_x = (int)(game->player.x / BLOCK);
	game->rcast.map_y = (int)(game->player.y / BLOCK);
	game->rcast.ray_x = cos(ray_angle);
	game->rcast.ray_y = sin(ray_angle);
	game->rcast.dist_x = fabs(BLOCK / game->rcast.ray_x);
	game->rcast.dist_y = fabs(BLOCK / game->rcast.ray_y);
	grid_pos_init(game);
	side = grid_move(game);
	dist = grid_dist(game, side, ray_angle);
	col.block = game->map.grid[game->rcast.map_y][game->rcast.map_x];
	if (side == 0)
		wall_x = game->player.y + dist * game->rcast.ray_y;
	else
		wall_x = game->player.x + dist * game->rcast.ray_x;
	col.dist = dist;
	col.wall_x = wall_x / BLOCK - floor(wall_x / BLOCK);
	col.screen_x = screen_x;
	col.side = side;
	draw_col(&col, game);
}
