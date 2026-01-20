/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:18:08 by diespino          #+#    #+#             */
/*   Updated: 2026/01/19 17:49:17 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// Raycasting simple
void	draw_col(double dist, int color, int screen_x, t_game *game)
{
	double	height;
	int	start_y;
	int	end_y;

	height = (BLOCK / dist) * (WIDTH / 2.0);
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
}

int	get_wall_color(double ray_x, double prev_x, double ray_angle)
{
	int	map_x;
	int	prev_map_x;

	map_x = (int)(ray_x / BLOCK);
	prev_map_x = (int)(prev_x / BLOCK);
	if (map_x != prev_map_x)
	{
		if (cos(ray_angle) > 0)
			return (0x0000FFFF);// EAST [BLUE]
		else
			return (0xFF0000FF);// WEST [RED]
	}
	else
	{
		if (sin(ray_angle) > 0)
			return (0x00FFFFFF);// SOUTH [LIGTH BLUE]
		else
			return (0x00FF00FF);// NORTH [GREEN]
	}
}

void	draw_line(t_game *game, double ray_angle, int screen_x)
{
	double	ray_x;
	double	ray_y;
	double	prev_x;
	double	dist;
	int	color;

	ray_x = game->player.x;
	ray_y = game->player.y;
	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			pixel_put(game, (int)ray_x, (int)ray_y, 0xFF0000FF);
		prev_x = ray_x;
		ray_x += cos(ray_angle);
		ray_y += sin(ray_angle);
	}
	if (!DEBUG)
	{
		color = get_wall_color(ray_x, prev_x, ray_angle);
		dist = fixed_dist(ray_x, ray_y, game);
		draw_col(dist, color, screen_x, game);
	}
}
