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


int	validate_rgb_count(char **rgb)
{
	int	count;

	count = 0;
	while (rgb[count])
		count++;
	if (count != 3)
	{
		free_rgb_array(rgb);
		return (printf("Error\nRGB must have exactly 3 values\n"), 0);
	}
	return (1);
}

int	validate_rgb_range(char **rgb, int *r, int *g, int *b)
{
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		free_rgb_array(rgb);
		return (printf("Error\nRGB values must be in range [0-255]\n"), 0);
	}
	return (1);
}