/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:42:46 by dmendoza          #+#    #+#             */
/*   Updated: 2026/04/09 15:31:40 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_cell_color(t_game *game, int map_x, int map_y)
{
	char	cell;

	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return (0x00000000);
	cell = game->map.grid[map_y][map_x];
	if (cell == '1')
		return (0x000000FF);
	if (cell == ' ')
		return (0x00000000);
	if (cell == 'D')
		return (0x00FF00FF);
	return (0x808080FF);
}

static void	draw_mm_pixel(t_game *game, int dx, int dy)
{
	t_mmpos		pos;
	double		cos_a;
	double		sin_a;
	uint32_t	color;

	cos_a = cos(-game->player.angle + PI / 2);
	sin_a = sin(-game->player.angle + PI / 2);
	pos.map_x = (int)(game->player.x / BLOCK + ((-dx) * cos_a - dy * sin_a) / MM_SCALE);
	pos.map_y = (int)(game->player.y / BLOCK - ((-dx) * sin_a + dy * cos_a) / MM_SCALE);
	pos.screen_x = MINIMAP_PADDING + MM_RADIUS + dx;
	pos.screen_y = MINIMAP_PADDING + MM_RADIUS + dy;
	color = get_cell_color(game, pos.map_x, pos.map_y);
	pixel_put(game, pos.screen_x, pos.screen_y, color);
}

static void	draw_mm_border(t_game *game)
{
	int	dx;
	int	dy;
	int	dist;

	dy = -MM_RADIUS - 2;
	while (dy <= MM_RADIUS + 2)
	{
		dx = -MM_RADIUS - 2;
		while (dx <= MM_RADIUS + 2)
		{
			dist = dx * dx + dy * dy;
			if (dist >= (MM_RADIUS) * (MM_RADIUS)
				&& dist <= (MM_RADIUS + 2) * (MM_RADIUS + 2))
				pixel_put(game, MINIMAP_PADDING + MM_RADIUS + dx,
					MINIMAP_PADDING + MM_RADIUS + dy, 0xFFFFFFFF);
			dx++;
		}
		dy++;
	}
}

static void	draw_mm_player(t_game *game)
{
	int	cx;
	int	cy;
	int	i;
	int	j;

	cx = MINIMAP_PADDING + MM_RADIUS;
	cy = MINIMAP_PADDING + MM_RADIUS;
	i = 0;
	while (i <= 4)
	{
		j = -i;
		while (j <= i)
		{
			pixel_put(game, cx + j, cy + i * 2, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	dx;
	int	dy;

	if (!game || !game->map.grid || game->map.height == 0)
		return ;
	dy = -MM_RADIUS;
	while (dy <= MM_RADIUS)
	{
		dx = -MM_RADIUS;
		while (dx <= MM_RADIUS)
		{
			if (dx * dx + dy * dy <= MM_RADIUS * MM_RADIUS
				&& (dx != 0 || dy != 0))
				draw_mm_pixel(game, dx, dy);
			dx++;
		}
		dy++;
	}
	draw_mm_border(game);
	draw_mm_player(game);
}
