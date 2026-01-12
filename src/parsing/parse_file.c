
#include "cub3d.h"

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)))
	{
		printf("Error\nFile must have .cub extension\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", filename);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_identifier(line, game))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!validate_identifiers(game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}