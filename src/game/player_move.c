/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:58:57 by diespino          #+#    #+#             */
/*   Updated: 2026/01/19 17:48:22 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# include "cub3d.h"
# include "test.h"

bool	touch(double ray_x, double ray_y, t_game *game)
{
	int	x;
	int	y;

	x = (int)(ray_x / BLOCK);
	y = (int)(ray_y / BLOCK);

	if (y < 0 || x < 0 || !game->map.grid[y] || !game->map.grid[y][x])
		return (true);
	return (game->map.grid[y][x] == '1');
}

static void	move_forward_backward(double dir_x, double dir_y, t_game *game)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x = game->player.x + dir_x;
		new_y = game->player.y + dir_y;
		if(!touch(new_x, new_y, game))
		{
			game->player.x += dir_x;
			game->player.y += dir_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_x = game->player.x - dir_x;
		new_y = game->player.y - dir_y;
		if(!touch(new_x, new_y, game))
		{
			game->player.x -= dir_x;
			game->player.y -= dir_y;
		}
	}
}

static void	strafe_move(double dir_x, double dir_y, t_game *game)
{
	double  new_x;
	double  new_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		new_x = game->player.x + dir_y;
		new_y = game->player.y - dir_x;
		if(!touch(new_x, new_y, game))
		{
			game->player.x += dir_y;
			game->player.y -= dir_x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new_x = game->player.x - dir_y;
		new_y = game->player.y + dir_x;
		if(!touch(new_x, new_y, game))
		{
			game->player.x -= dir_y;
			game->player.y += dir_x;
		}
	}
}

void    move_player(t_game *game, t_player *player)
{
	double	speed;
	double	rot_speed;
	double	dir_x;
	double	dir_y;
	
	speed = 3.0;// velocidad de movimiento
	rot_speed = 0.04;// velocidad de camara
//
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->angle -= rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->angle += rot_speed;
//
	if (player->angle > 2.0 * PI)
		player->angle = 0.0;
	if (player->angle < 0.0)
		player->angle = 2.0 * PI;
//
	dir_x = cos(player->angle) * speed;
	dir_y = sin(player->angle) * speed;
//
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) ||
			mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward_backward(dir_x, dir_y, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) ||
			mlx_is_key_down(game->mlx, MLX_KEY_D))
		strafe_move(dir_x, dir_y, game);
}

// static void     pixel_put(t_game *game, int x, int y, uint32_t color)
void	init_player(t_player *player)
{
	player->x = WIDTH / 2.0;
	player->y = HEIGHT / 2.0;
	player->angle = PI / 2.0;
}
