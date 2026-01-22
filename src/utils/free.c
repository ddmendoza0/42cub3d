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
}

static void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return;
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

void	free_game(t_game *game)
{
	if (!game)
		return;
	free_textures(&game->textures);
	free_map(&game->map);
	if (game->tex_north)
		mlx_delete_texture(game->tex_north);
	if (game->tex_south)
		mlx_delete_texture(game->tex_south);
	if (game->tex_east)
		mlx_delete_texture(game->tex_east);
	if (game->tex_west)
		mlx_delete_texture(game->tex_west);
}