/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:42:46 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:46:46 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MM_RADIUS 100
# define MM_SCALE 12

static uint32_t	get_cell_color(t_game *game, int map_x, int map_y)
{
	char	cell;

	if (map_x < 0 || map_y < 0 || map_x >= game->map.width || map_y >= game->map.height)
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
	double		rotated_x;
	double		rotated_y;
	int			map_x;
	int			map_y;
	uint32_t	color;
	int			screen_x;
	int			screen_y;
	double		cos_a;
	double		sin_a;

	cos_a = cos(-game->player.angle + PI / 2);
	sin_a = sin(-game->player.angle + PI / 2);
	rotated_x = dx * cos_a - dy * sin_a;
	rotated_y = dx * sin_a + dy * cos_a;
	map_x = (int)(game->player.x / BLOCK + rotated_x / MM_SCALE);
	map_y = (int)(game->player.y / BLOCK + rotated_y / MM_SCALE);
	color = get_cell_color(game, map_x, map_y);
	screen_x = MINIMAP_PADDING + MM_RADIUS + dx;
	screen_y = MINIMAP_PADDING + MM_RADIUS + dy;
	pixel_put(game, screen_x, screen_y, color);
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
			if (dx * dx + dy * dy <= MM_RADIUS * MM_RADIUS && (dx != 0 || dy != 0))
				draw_mm_pixel(game, dx, dy);
			dx++;
		}
		dy++;
	}
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS - 1, MINIMAP_PADDING + MM_RADIUS - 1, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS, MINIMAP_PADDING + MM_RADIUS - 1, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS + 1, MINIMAP_PADDING + MM_RADIUS - 1, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS - 1, MINIMAP_PADDING + MM_RADIUS, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS, MINIMAP_PADDING + MM_RADIUS, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS + 1, MINIMAP_PADDING + MM_RADIUS, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS - 1, MINIMAP_PADDING + MM_RADIUS + 1, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS, MINIMAP_PADDING + MM_RADIUS + 1, 0xFF0000FF);
	pixel_put(game, MINIMAP_PADDING + MM_RADIUS + 1, MINIMAP_PADDING + MM_RADIUS + 1, 0xFF0000FF);
}
//#include "cub3d.h"
//
//static int	calculate_scale(t_game *game)
//{
//	int	scale_x;
//	int	scale_y;
//	int	scale;
//
//	scale_x = (MINIMAP_SIZE - 10) / game->map.width;
//	scale_y = (MINIMAP_SIZE - 10) / game->map.height;
//	if (scale_x < scale_y)
//		scale = scale_x;
//	else
//		scale = scale_y;
//	if (scale < 1)
//		scale = 1;
//	return (scale);
//}
//
//static void	draw_minimap_tile(t_game *game, int x, int y, uint32_t color, int scale)
//{
//	int	i;
//	int	j;
//	int	screen_x;
//	int	screen_y;
//
//	screen_x = scale * x;
//	screen_y = scale * y;
//	screen_x += WIDTH - (game->map.width * scale + MINIMAP_PADDING);
//	screen_y += HEIGHT - (game->map.height * scale + MINIMAP_PADDING);
//	j = 0;
//	while (j < scale)
//	{
//		i = 0;
//		while (i < scale)
//		{
//			if (screen_x + i < WIDTH && screen_y + j < HEIGHT)
//				pixel_put(game, screen_x + i, screen_y + j, color);
//			i++;
//		}
//		j++;
//	}
//}
//
//void	draw_minimap(t_game *game)
//{
//	int			x;
//	int			y;
//	int			player_x;
//	int			player_y;
//	uint32_t	color;
//	int			scale;
//
//	if (!game || !game->map.grid || game->map.height == 0)
//		return ;
//	scale = calculate_scale(game);
//	player_x = (int)(game->player.x / BLOCK);
//	player_y = (int)(game->player.y / BLOCK);
//	y = 0;
//	while (y < game->map.height)
//	{
//		x = 0;
//		while (x < game->map.width)
//		{
//			if (game->map.grid[y][x] == '1')
//				color = 0x000000FF;
//			else if (game->map.grid[y][x] == ' ')
//				color = 0x80808080;
//			else if (game->map.grid[y][x] == 'D')
//				color = 0x00FF00FF;
//			else
//				color = 0xFFFFFFFF;
//			if (player_x == x && player_y == y)
//				color = 0xFF0000FF;
//			draw_minimap_tile(game, x, y, color, scale);
//			x++;
//		}
//		y++;
//	}
//}
