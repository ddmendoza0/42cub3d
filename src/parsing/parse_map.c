/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:13 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:22:15 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	normalize_map(t_game *game)
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
		free(game->map.grid[i]);
		i++;
	}
	new_grid[i] = NULL;
	free(game->map.grid);
	game->map.grid = new_grid;
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

static char	**convert_list_to_array(t_list *map_lines, int height)
{
	char	**grid;
	int		i;
	t_list	*current;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	current = map_lines;
	i = 0;
	while (current)
	{
		grid[i] = ft_strdup((char *)current->content);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		if (grid[i][ft_strlen(grid[i]) - 1] == '\n')
			grid[i][ft_strlen(grid[i]) - 1] = '\0';
		current = current->next;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

int	parse_map(int fd, t_game *game, char *first_line)
{
	char	*line;
	t_list	*map_lines;
	t_list	*new_node;
	int		height;

	map_lines = NULL;
	height = 0;
	if (first_line && is_map_line(first_line))
	{
		new_node = ft_lstnew(first_line);
		if (!new_node)
		{
			free(first_line);
			return (0);
		}
		ft_lstadd_back(&map_lines, new_node);
		height++;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			new_node = ft_lstnew(line);
			if (!new_node)
			{
				free(line);
				ft_lstclear(&map_lines, free);
				return (0);
			}
			ft_lstadd_back(&map_lines, new_node);
			height++;
		}
		else if (line[0] != '\n' && map_lines != NULL)
		{
			free(line);
			ft_lstclear(&map_lines, free);
			return (printf("Error\nInvalid map format\n"), 0);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	game->map.grid = convert_list_to_array(map_lines, height);
	game->map.height = height;
	ft_lstclear(&map_lines, free);
	if (!game->map.grid)
		return (0);
	if (!calculate_map_width(game))
		return (0);
	if (!validate_map_characters(game))
		return (0);
	if (!validate_map_closed(game))
		return (0);
	if (!normalize_map(game))
		return (printf("Error\nFailed to normalize map\n"), 0);
	return (1);
}
