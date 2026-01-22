
#include "cub3d.h"

void	pixel_put(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
}

void	clear_img(t_game *game)
{
	int			x;
	int			y;
	uint32_t	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y < HEIGHT / 2)
		{
			color = (game->colors.ceiling_r << 24) 
				| (game->colors.ceiling_g << 16) 
				| (game->colors.ceiling_b << 8) 
				| 0xFF;
		}
		else
		{
			color = (game->colors.floor_r << 24) 
				| (game->colors.floor_g << 16) 
				| (game->colors.floor_b << 8) 
				| 0xFF;
		}
		while (x < WIDTH)
		{
			pixel_put(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_loop(void *param)
{
	t_game		*game;
	t_player	*player;
	double		fraction;
	double		ray_angle;
	int			i;

	game = (t_game *)param;
	player = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	move_player(game, player);
	clear_img(game);
	fraction = (PI / 3.0) / (double)WIDTH;
	ray_angle = player->angle - (PI / 6.0);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(game, ray_angle, i);
		ray_angle += fraction;
		i++;
	}
}