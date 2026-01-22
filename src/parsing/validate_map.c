#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	calculate_map_width(t_game *game)
{
	int	i;
	int	len;
	int	max_width;

	max_width = 0;
	i = 0;
	while (i < game->map.height)
	{
		len = ft_strlen(game->map.grid[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	game->map.width = max_width;
	return (1);
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_char(game->map.grid[i][j]))
				return (printf("Error\nInvalid character in map: %c (ASCII: %d)\n", game->map.grid[i][j], game->map.grid[i][j]), 0);
			if (is_player(game->map.grid[i][j]))
			{
				player_count++;
				game->player.x = j;
				game->player.y = i;
				game->player.orientation = game->map.grid[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("Error\nMap must have exactly one player\n"), 0);
	return (1);
}

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		copy[i] = ft_strdup(game->map.grid[i]);
		if (!copy[i])
			return (NULL); // TODO: free previous
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_map_copy(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	flood_fill(char **map, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->map.height || x < 0)
		return (1);
	if (x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == ' ')
	{
		if (y == 0 || y == game->map.height - 1 
			|| x == 0 || x >= game->map.width - 1)
			return (0);
	}
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	map[y][x] = 'X';
	if (!flood_fill(map, x + 1, y, game))
		return (0);
	if (!flood_fill(map, x - 1, y, game))
		return (0);
	if (!flood_fill(map, x, y + 1, game))
		return (0);
	if (!flood_fill(map, x, y - 1, game))
		return (0);
	
	return (1);
}

int	validate_map_closed(t_game *game)
{
	char	**map_copy;
	int		result;

	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	
	result = flood_fill(map_copy, (int)game->player.x, 
		(int)game->player.y, game);
	
	free_map_copy(map_copy, game->map.height);
	
	if (!result)
		return (printf("Error\nMap is not closed by walls\n"), 0);
	
	return (1);
}