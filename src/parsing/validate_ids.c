#include "cub3d.h"

int	validate_identifiers(t_game *game)
{
	if (!game->has_north)
		return (printf("Error\nMissing identifier: NO\n"), 0);
	if (!game->has_south)
		return (printf("Error\nMissing identifier: SO\n"), 0);
	if (!game->has_west)
		return (printf("Error\nMissing identifier: WE\n"), 0);
	if (!game->has_east)
		return (printf("Error\nMissing identifier: EA\n"), 0);
	if (!game->has_floor)
		return (printf("Error\nMissing identifier: F\n"), 0);
	if (!game->has_ceiling)
		return (printf("Error\nMissing identifier: C\n"), 0);
	return (1);
}

int validate_texture_file(char* path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".png", 4) != 0)
		return (printf("Error\nTexture file must have .png extension: %s\n", path), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open texture file: %s\n", path), 0);
	close(fd);
	return (1);
}