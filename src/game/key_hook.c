/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:53:21 by diespino          #+#    #+#             */
/*   Updated: 2026/04/09 15:20:20 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	open_door(t_game *game, t_player *player)
{
	int		grid_x;
	int		grid_y;
	double	check_x;
	double	check_y;

	check_x = player->x + cos(player->angle) * BLOCK;
	check_y = player->y + sin(player->angle) * BLOCK;
	grid_x = (int)(check_x / BLOCK);
	grid_y = (int)(check_y / BLOCK);
	if (grid_y < 0 || grid_y >= game->map.height
		|| grid_x < 0 || grid_x >= game->map.width)
		return ;
	if (game->map.grid[grid_y][grid_x] == 'D')
		game->map.grid[grid_y][grid_x] = 'O';
	else if (game->map.grid[grid_y][grid_x] == 'O')
		game->map.grid[grid_y][grid_x] = 'D';
}

void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		open_door(game, &game->player);
}
