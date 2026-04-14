/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 08:35:55 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:15:35 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(char *filename)
{
	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)))
	{
		printf("Error\nFile must have .cub extension\n");
		return (0);
	}
	return (1);
}

static int	is_map_start(char *line)
{
	if (line[0] == '0' || line[0] == '1' || line[0] == ' '
		|| line[0] == 'D')
		return (1);
	if (is_player(line[0]) && line[1] != 'O' && line[1] != 'E'
		&& line[1] != 'A' && line[1] != 'W')
		return (1);
	return (0);
}

static char	*parse_identifiers_loop(int fd, t_game *game, int *error)
{
	char	*line;

	*error = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_start(line))
			return (line);
		if (!parse_identifier(line, game))
		{
			free(line);
			*error = 1;
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	parse_sections(int fd, t_game *game)
{
	char	*line;
	int		error;

	line = parse_identifiers_loop(fd, game, &error);
	if (error)
		return (0);
	if (!validate_identifiers(game))
	{
		free(line);
		return (0);
	}
	if (!parse_map(fd, game, line))
		return (0);
	return (1);
}

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;

	if (!check_extension(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", filename);
		return (0);
	}
	if (!parse_sections(fd, game))
	{
		close(fd);
		free_game(game);
		return (0);
	}
	close(fd);
	return (1);
}
