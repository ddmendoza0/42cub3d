
#include "cub3d.h"

static void	init_player(t_game *game)
{
	game->player.x = (game->player.x * BLOCK) + (BLOCK / 2.0);
	game->player.y = (game->player.y * BLOCK) + (BLOCK / 2.0);
	if (game->player.orientation == 'N')
		game->player.angle = PI / 2.0;
	else if (game->player.orientation == 'S')
		game->player.angle = 3.0 * PI / 2.0;
	else if (game->player.orientation == 'E')
		game->player.angle = 0.0;
	else if (game->player.orientation == 'W')
		game->player.angle = PI;
}

int	init_game(t_game *game)
{
	init_player(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		return (0);
	}
	return (1);
}