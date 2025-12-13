
#include "cub3d.h"

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;

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
	(void)game;
	// TODO: Leer y parsear el archivo línea por línea
	
	close(fd);
	return (1);
}