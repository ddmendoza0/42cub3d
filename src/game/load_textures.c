/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:42:19 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:42:31 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *game)
{
	game->tex_north = mlx_load_png(game->textures.north);
	if (!game->tex_north)
		return (printf("Error\nFailed to load north texture\n"), 0);
	game->tex_south = mlx_load_png(game->textures.south);
	if (!game->tex_south)
		return (free_game(game), printf("Error\nFailed to load south texture\n"), 0);
	game->tex_east = mlx_load_png(game->textures.east);
	if (!game->tex_east)
		return (free_game(game), printf("Error\nFailed to load east texture\n"), 0);
	game->tex_west = mlx_load_png(game->textures.west);
	if (!game->tex_west)
		return (free_game(game), printf("Error\nFailed to load west texture\n"), 0);
	if (game->textures.door)
	{
		game->tex_door = mlx_load_png(game->textures.door);
		if (!game->tex_door)
			return (free_game(game), printf("Error\nFailed to load door texture\n"), 0);
	}
	return (1);
}
