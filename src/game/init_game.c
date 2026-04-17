/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:41:21 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:41:54 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_game *game)
{
	game->player.x = (game->player.x * BLOCK) + (BLOCK / 2.0);
	game->player.y = (game->player.y * BLOCK) + (BLOCK / 2.0);
	if (game->player.orientation == 'N')
		game->player.angle = 3.01 * PI / 2.0;
	else if (game->player.orientation == 'S')
		game->player.angle = PI / 2.0;
	else if (game->player.orientation == 'E')
		game->player.angle = 0.0;
	else if (game->player.orientation == 'W')
		game->player.angle = PI + 0.01;
}

int	init_game(t_game *game)
{
	init_player(game);
	if (!load_textures(game))
		return (0);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		return (0);
	}
	mlx_key_hook(game->mlx, key_callback, game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	return (1);
}
