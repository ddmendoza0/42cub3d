#include "cub3d.h"

int	main(int argc, char** argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	// TODO: Validar extensión .cub
	// TODO: Parsear el archivo
	// TODO: Validar el mapa
	// TODO: Inicializar MLX y renderizar

	printf("cub3D started with map: %s\n", argv[1]);
	return (0);
}