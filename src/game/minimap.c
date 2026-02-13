
#include "cub3d.h"

static void	draw_minimap_tile(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	screen_x = MINIMAP_PADDING + (x * MINIMAP_SCALE);
	screen_y = MINIMAP_PADDING + (y * MINIMAP_SCALE);
	j = 0;
	while (j < MINIMAP_SCALE)
	{
		i = 0;
		while (i < MINIMAP_SCALE)
		{
			if (screen_x + i < WIDTH && screen_y + j < HEIGHT)
				pixel_put(game, screen_x + i, screen_y + j, color);
			i++;
		}
		j++;
	}
}

void draw_minimap(t_game* game)
{
	int			x;
	int			y;
	uint32_t	color;


	y = 0;
	while (y < game->map.height && y * MINIMAP_SCALE < MINIMAP_SIZE)
	{
		x = 0;
		while (x < game->map.width && x * MINIMAP_SCALE < MINIMAP_SIZE)
		{
			if (game->map.grid[y][x] == '1')
				color = 0x000000FF;
			else if (game->map.grid[y][x] == ' ')
				color = 0x80808080;
			else
				color = 0xFFFFFFFF;
			if ((int)game->player.x / BLOCK == x && (int)game->player.y / BLOCK == y)
				color = 0xFF0000FF;
			draw_minimap_tile(game, x, y, color);
			x++;
		}
		y++;
	}
}