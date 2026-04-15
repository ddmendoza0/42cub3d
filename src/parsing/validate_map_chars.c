/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:29 by dmendoza          #+#    #+#             */
/*   Updated: 2026/04/15 15:44:01 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ' || c == 'D');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player(t_game *game, int i, int j)
{
	game->player.x = j;
	game->player.y = i;
	game->player.orientation = game->map.grid[i][j];
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (++i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_char(game->map.grid[i][j]))
				return (printf("Error\n%s %c\n", ERR_MAP_CHR,
						game->map.grid[i][j]), 0);
			if (is_player(game->map.grid[i][j]))
			{
				player_count++;
				set_player(game, i, j);
			}
			j++;
		}
	}
	if (player_count != 1)
		return (printf("Error\nMap must have exactly one player\n"), 0);
	return (1);
}
