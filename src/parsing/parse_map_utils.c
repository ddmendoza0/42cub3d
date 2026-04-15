/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:28:46 by diespino          #+#    #+#             */
/*   Updated: 2026/04/15 15:28:50 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*pad_line(char *line, int target_width)
{
	char	*padded;
	int		i;
	int		len;

	len = ft_strlen(line);
	if (len >= target_width)
		return (ft_strdup(line));
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

static char	*dup_strip(char *content)
{
	char	*line;
	int		len;

	line = ft_strdup(content);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

char	**convert_list_to_array(t_list *map_lines, int height)
{
	char	**grid;
	t_list	*current;
	int		i;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	current = map_lines;
	i = 0;
	while (current)
	{
		grid[i] = dup_strip((char *)current->content);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

static void	swap_grid(t_game *game, char **new_grid)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = new_grid;
}

int	normalize_map(t_game *game)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = pad_line(game->map.grid[i], game->map.width);
		if (!new_grid[i])
		{
			while (--i >= 0)
				free(new_grid[i]);
			free(new_grid);
			return (0);
		}
		i++;
	}
	new_grid[i] = NULL;
	swap_grid(game, new_grid);
	return (1);
}
