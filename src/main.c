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
/*	if (!init_game(&game))
	{
		free_game(&game);
		printf("Error\nFailed to initialize game\n");
		return (1);
	}
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);*/

	printf("Parsing successful!\n");
	printf("Map size: %dx%d\n", game.map.width, game.map.height);
	printf("Player at: (%.0f, %.0f) facing %c\n", game.player.x, game.player.y, game.player.orientation);
	printf("Textures:\n  North: %s\n  South: %s\n  West: %s\n  East: %s\n",
		game.textures.north, game.textures.south, game.textures.west, game.textures.east);
	printf("Colors:\n  Floor: %d,%d,%d\n  Ceiling: %d,%d,%d\n",
		game.colors.floor_r, game.colors.floor_g, game.colors.floor_b,
		game.colors.ceiling_r, game.colors.ceiling_g, game.colors.ceiling_b);

	free_game(&game);
	return (0);
}