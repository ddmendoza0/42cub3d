/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:40:23 by dmendoza          #+#    #+#             */
/*   Updated: 2026/04/10 14:13:34 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_textures *textures)
{
	if (textures->north)
	{
		free(textures->north);
		textures->north = NULL;
	}
	if (textures->south)
	{
		free(textures->south);
		textures->south = NULL;
	}
	if (textures->west)
	{
		free(textures->west);
		textures->west = NULL;
	}
	if (textures->east)
	{
		free(textures->east);
		textures->east = NULL;
	}
	if (textures->door)
	{
		free(textures->door);
		textures->door = NULL;
	}
}

void	free_rgb_array(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

static void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

static void	free_mlx_textures(t_game *game)
{
	if (game->tex_north)
	{
		mlx_delete_texture(game->tex_north);
		game->tex_north = NULL;
	}
	if (game->tex_south)
	{
		mlx_delete_texture(game->tex_south);
		game->tex_south = NULL;
	}
	if (game->tex_east)
	{
		mlx_delete_texture(game->tex_east);
		game->tex_east = NULL;
	}
	if (game->tex_west)
	{
		mlx_delete_texture(game->tex_west);
		game->tex_west = NULL;
	}
	if (game->tex_door)
	{
		mlx_delete_texture(game->tex_door);
		game->tex_door = NULL;
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(&game->textures);
	free_map(&game->map);
	free_mlx_textures(game);
}
