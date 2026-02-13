#include "cub3d.h"

static int	parse_texture(char *line, char **texture)
{
	char	*path;
	int		len;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	path = ft_strdup(line);
	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	if (!validate_texture_file(path))
	{
		free(path);
		return (0);
	}
	*texture = path;
	return (1);
}

static int	parse_color(char *line, t_colors *colors, int is_floor)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	if (!validate_rgb_count(rgb))
		return (0);
	if (!validate_rgb_range(rgb, &r, &g, &b))
		return (0);
	if (is_floor)
	{
		colors->floor_r = r;
		colors->floor_g = g;
		colors->floor_b = b;
	}
	else
	{
		colors->ceiling_r = r;
		colors->ceiling_g = g;
		colors->ceiling_b = b;
	}
	free_rgb_array(rgb);
	return (1);
}

static int	parse_north_south(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (game->has_north)
			return (printf("Error\nDuplicate identifier: NO\n"), 0);
		game->has_north = 1;
		return (parse_texture(line, &game->textures.north));
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (game->has_south)
			return (printf("Error\nDuplicate identifier: SO\n"), 0);
		game->has_south = 1;
		return (parse_texture(line, &game->textures.south));
	}
	return (-1);
}

static int	parse_west_east(char *line, t_game *game)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (game->has_west)
			return (printf("Error\nDuplicate identifier: WE\n"), 0);
		game->has_west = 1;
		return (parse_texture(line, &game->textures.west));
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (game->has_east)
			return (printf("Error\nDuplicate identifier: EA\n"), 0);
		game->has_east = 1;
		return (parse_texture(line, &game->textures.east));
	}
	return (-1);
}

static int	parse_floor_ceiling(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->has_floor)
			return (printf("Error\nDuplicate identifier: F\n"), 0);
		game->has_floor = 1;
		return (parse_color(line, &game->colors, 1));
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->has_ceiling)
			return (printf("Error\nDuplicate identifier: C\n"), 0);
		game->has_ceiling = 1;
		return (parse_color(line, &game->colors, 0));
	}
	return (-1);
}

int	parse_identifier(char *line, t_game *game)
{
	int	result;

	result = parse_north_south(line, game);
	if (result != -1)
		return (result);
	result = parse_west_east(line, game);
	if (result != -1)
		return (result);
	result = parse_floor_ceiling(line, game);
	if (result != -1)
		return (result);
	return (1);
}