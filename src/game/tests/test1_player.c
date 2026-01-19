/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:58:57 by diespino          #+#    #+#             */
/*   Updated: 2026/01/19 15:14:32 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
//# include "test.h"

//void	move_player(mlx_t *mlx, t_player *player)
void    move_player(t_game *game, t_player *player)
{
	double	speed;
	double	rot_speed;
	double	dir_x;
	double	dir_y;
	double	new_x;
	double	new_y;
	
	speed = 3.0;// velocidad de movimiento
	rot_speed = 0.04;// velocidad de camara

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->angle -= rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->angle += rot_speed;
//	rotacion de camara con flechas
//
	if (player->angle > 2.0 * PI)
		player->angle = 0.0;
	if (player->angle < 0.0)
		player->angle = 2.0 * PI;
//	rango del fov
//
	dir_x = cos(player->angle) * speed;
	dir_y = sin(player->angle) * speed;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x = player->x + dir_x;
		new_y = player->y + dir_y;
		if(!touch(new_x, new_y, game))
		{
			player->x += dir_x;
			player->y += dir_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_x = player->x - dir_x;
		new_y = player->y - dir_y;
		if(!touch(new_x, new_y, game))
		{
			player->x -= dir_x;
			player->y -= dir_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		new_x = player->x + dir_y;
		new_y = player->y - dir_x;
		if(!touch(new_x, new_y, game))
		{
			player->x += dir_y;
			player->y -= dir_x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new_x = player->x - dir_y;
		new_y = player->y + dir_x;
		if(!touch(new_x, new_y, game))
		{
			player->x -= dir_y;
			player->y += dir_x;
		}
	}
}
/*
// static void     pixel_put(t_game *game, int x, int y, uint32_t color)
void	init_player(t_player *player)
{
	player->x = WIDTH / 2.0;
	player->y = HEIGHT / 2.0;
	player->angle = PI / 2.0;
}*/
