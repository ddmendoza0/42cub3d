#include "cub3d.h"

static int	parse_texture(char *line, char **texture)
{
	char	*path;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	path = ft_strdup(line);
	if (!path)
		return (0);
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = '\0';
	*texture = path;
	return (1);
}

static int	parse_color(char *line, t_colors *colors, int is_floor)
{
	char	**rgb;
	int		r, g, b;

	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
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
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	return (1);
}

int	parse_identifier(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line, &game->textures.north));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line, &game->textures.south));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line, &game->textures.west));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line, &game->textures.east));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line, &game->colors, 1));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line, &game->colors, 0));
	return (1);
}