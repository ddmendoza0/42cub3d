/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bounds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:29:01 by diespino          #+#    #+#             */
/*   Updated: 2026/04/15 15:29:07 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'D' || is_player(c));
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
