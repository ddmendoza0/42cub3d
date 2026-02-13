#include "cub3d.h"

static int	calculate_scale(t_game *game)
{
	int	scale_x;
	int	scale_y;

	scale_x = (MINIMAP_SIZE - 10) / game->map.width;
	scale_y = (MINIMAP_SIZE - 10) / game->map.height;
	if (scale_x < scale_y)
		return (scale_x < 1 ? 1 : scale_x);
	return (scale_y < 1 ? 1 : scale_y);
}

static void	draw_minimap_tile(t_game *game, int x, int y, uint32_t color, int scale)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	screen_x = MINIMAP_PADDING + (x * scale);
	screen_y = MINIMAP_PADDING + (y * scale);
	j = 0;
	while (j < scale)
	{
		i = 0;
		while (i < scale)
		{
			if (screen_x + i < WIDTH && screen_y + j < HEIGHT)
				pixel_put(game, screen_x + i, screen_y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_game *game)
{
	int			x;
	int			y;
	int			player_x;
	int			player_y;
	uint32_t	color;
	int			scale;

	if (!game || !game->map.grid || game->map.height == 0)
		return;
	scale = calculate_scale(game);
	player_x = (int)(game->player.x / BLOCK);
	player_y = (int)(game->player.y / BLOCK);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '1')
				color = 0x000000FF;
			else if (game->map.grid[y][x] == ' ')
				color = 0x80808080;
			else
				color = 0xFFFFFFFF;
			if (player_x == x && player_y == y)
				color = 0xFF0000FF;
			draw_minimap_tile(game, x, y, color, scale);
			x++;
		}
		y++;
	}
}