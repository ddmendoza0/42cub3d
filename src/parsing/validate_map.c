/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:29 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:30:05 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c =='D');
}


static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'D' || is_player(c));
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
				return (printf("Error\nInvalid character in map: %c\n", game->map.grid[i][j]), 0);
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

static int	check_row(char *row, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (is_walkable(row[j]))
		{
			if (j == 0 || j == width - 1)
				return (0);
			if (row[j - 1] == ' ' || row[j + 1] == ' ')
				return (0);
		}
		j++;
	}
	return (1);
}

static int	check_col(char **map, int x, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		if (is_walkable(map[y][x]))
		{
			if (y == 0 || y == height - 1)
				return (0);
			if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
				return (0);
		}
		y++;
	}
	return (1);
}

int	validate_map_closed(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if (!check_row(game->map.grid[i], game->map.width))
			return (printf("Error\nMap is not closed by walls\n"), 0);
		i++;
	}
	i = 0;
	while (i < game->map.width)
	{
		if (!check_col(game->map.grid, i, game->map.height))
			return (printf("Error\nMap is not closed by walls\n"), 0);
		i++;
	}
	return (1);
}