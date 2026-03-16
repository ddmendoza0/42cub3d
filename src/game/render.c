/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:54:01 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:57:35 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
}

static uint32_t	get_row_color(t_game *game, int y)
{
	if (y < HEIGHT / 2)
		return ((game->colors.ceiling_r << 24)
			| (game->colors.ceiling_g << 16)
			| (game->colors.ceiling_b << 8) | 0xFF);
	return ((game->colors.floor_r << 24)
		| (game->colors.floor_g << 16)
		| (game->colors.floor_b << 8) | 0xFF);
}

static void	fill_row(t_game *game, int y, uint32_t color)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		pixel_put(game, x, y, color);
		x++;
	}
}

void	clear_img(t_game *game)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		fill_row(game, y, get_row_color(game, y));
		y++;
	}
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))// mantener pulsado
		mlx_close_window(game->mlx);
	mlx_key_hook(game->mlx, key_callback, game);// solo presion una vez
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
