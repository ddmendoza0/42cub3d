#include "cub3d.h"

int	main(int argc, char** argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_cub_file(argv[1], &game))
		return (1);
	if (!init_game(&game))
	{
		free_game(&game);
		printf("Error\nFailed to initialize game\n");
		return (1);
	}
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_game(&game);
	return (0);
}