/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:54:01 by dmendoza          #+#    #+#             */
/*   Updated: 2026/04/09 15:21:23 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
}

static void	fill_half(t_game *game, int start_y, int end_y, uint32_t color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	clear_img(t_game *game)
{
	uint32_t	ceiling;
	uint32_t	floor_color;

	ceiling = (game->colors.ceiling_r << 24)
		| (game->colors.ceiling_g << 16)
		| (game->colors.ceiling_b << 8) | 0xFF;
	floor_color = (game->colors.floor_r << 24)
		| (game->colors.floor_g << 16)
		| (game->colors.floor_b << 8) | 0xFF;
	fill_half(game, 0, HEIGHT / 2, ceiling);
	fill_half(game, HEIGHT / 2, HEIGHT, floor_color);
}

void	draw_loop(void *param)
{
	t_game		*game;
	t_player	*player;
	double		fraction;
	double		ray_angle;
	int			i;

	game = (t_game *)param;
	player = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	move_player(game, player);
	clear_img(game);
	fraction = (PI / 3.0) / (double)WIDTH;
	ray_angle = player->angle - (PI / 6.0);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(game, ray_angle, i);
		ray_angle += fraction;
		i++;
	}
	draw_minimap(game);
}
