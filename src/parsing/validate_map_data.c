/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:44:33 by diespino          #+#    #+#             */
/*   Updated: 2026/04/15 16:31:16 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_has_doors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'D')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	calculate_map_width(t_game *game)
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

int	validate_map_data(t_game *game)
{
	if (!calculate_map_width(game))
		return (0);
	if (!validate_map_characters(game))
		return (0);
	if (!normalize_map(game))
		return (printf("Error\nFailed to normalize map\n"), 0);
	if (!validate_map_closed(game))
		return (0);
	if (map_has_doors(game) && !game->has_door)
		return (printf("Error\n%s\n", ERR_NO_DO_ID), 0);
	return (1);
}
