/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:13 by dmendoza          #+#    #+#             */
/*   Updated: 2026/04/15 15:28:26 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (line[i] == '1' || line[i] == '0' || line[i] == 'D'
		|| is_player(line[i]));
}

static int	add_first_line(t_list **map_lines, char *first_line, int *height)
{
	t_list	*new_node;

	if (!first_line || !is_map_line(first_line))
		return (1);
	new_node = ft_lstnew(first_line);
	if (!new_node)
		return (free(first_line), 0);
	ft_lstadd_back(map_lines, new_node);
	(*height)++;
	return (1);
}

static int	process_line(t_list **map_lines, char *line, int *height)
{
	t_list	*new_node;

	if (is_map_line(line))
	{
		new_node = ft_lstnew(line);
		if (!new_node)
			return (free(line), ft_lstclear(map_lines, free), 0);
		ft_lstadd_back(map_lines, new_node);
		(*height)++;
	}
	else if (line[0] != '\n' && *map_lines != NULL)
		return (free(line), ft_lstclear(map_lines, free),
			printf("Error\nInvalid map format\n"), 0);
	else
		free(line);
	return (1);
}

static int	collect_lines(int fd, t_list **map_lines,
		char *first_line, int *height)
{
	char	*line;

	if (!add_first_line(map_lines, first_line, height))
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(map_lines, line, height))
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_map(int fd, t_game *game, char *first_line)
{
	t_list	*map_lines;
	int		height;

	map_lines = NULL;
	height = 0;
	if (!collect_lines(fd, &map_lines, first_line, &height))
		return (0);
	game->map.grid = convert_list_to_array(map_lines, height);
	game->map.height = height;
	ft_lstclear(&map_lines, free);
	if (!game->map.grid)
		return (0);
	return (validate_map_data(game));
}
