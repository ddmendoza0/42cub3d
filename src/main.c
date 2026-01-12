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
	// TODO: Inicializar MLX y renderizar

	printf("cub3D started with map: %s\n", argv[1]);
	free_game(game);
	return (0);
}