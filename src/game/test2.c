/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:50:12 by diespino          #+#    #+#             */
/*   Updated: 2026/01/19 17:19:10 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// typedef struct s_game
// {
//         mlx_t           *mlx;// Puntero a mlx
//         mlx_image_t     *img;// Imagen de mlx
//         t_player        player;// Jugador
//         char            **map;// Mapa
// }       t_game;

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "   111111111111111                        1111";
	map[1] = "   100000000000001                        1001";
	map[2] = "   1000000000111111111111111111111111111111001";
	map[3] = "   1000000000000010000000000000000000000000001";
	map[4] = "1111000000000000011111111111111111111111111111";
	map[5] = "100000000000101111";
	map[6] = "100000000000001";
	map[7] = "100011110000001";
	map[8] = "10001  10000001";
	map[9] = "11111  11111111";
	map[10] = NULL;
	return (map);
}

void	pixel_put(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
//	mete pixeles en imagen 
}

void	clear_img(t_game *game)
{
	int		x;
	int		y;
	uint32_t	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y < HEIGHT / 2 && !DEBUG)
			color = 0xFFFFFFFF;
		else
			color = 0x000000FF;
		while(x < WIDTH)
		{
			pixel_put(game, x, y, color);
			x++;
		}
		y++;
	}
}

// Dibujo de cuadrados (bloques de mapa y player)
// game, screen_x, start_y, 0x0000FFFF
void	draw_square(int x, int y, int size, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
		pixel_put(game, x + i++, y, 0x00FF00FF);// Norte [GREEN]
	i = 0;
	while (i < size)
		pixel_put(game, x, y + i++, 0xFF0000FF);// Oeste [RED]
	i = 0;
	while (i < size)
		pixel_put(game, x + size, y + i++, 0x0000FFFF);// Este [BLUE]
	i = 0;
	while (i < size)
		pixel_put(game, x + i++, y + size, 0x00FFFFFF);// Sur [YELLOW]
}

// Manda a draw_square() culaquier parte del mapa en la que haya 1
static void	draw_map(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	y = 0;
	map = game->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, game);
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
	int		i;

	game = (t_game *)param;
	player = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	move_player(game, player);
	clear_img(game);// Textura suelo/techo
	if (DEBUG)
	{
		draw_square((int)player->x, (int)player->y, 10, game);
		draw_map(game);
	}
	fraction = (PI / 3.0) / (double)WIDTH;
	ray_angle = player->angle - (PI / 6.0);
	i = -1;
	while(++i < WIDTH)
	{
		draw_line(game, ray_angle, i);
		ray_angle += fraction;
	}
}

void	init_game(t_game *game)
{
	init_player(&game->player);
//	iniciliza el player
	game->map = get_map();
//	parsea el mapa
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", false);
//		Tamano de ventana && nombre
	if (!game->mlx)
		exit(EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
//		Creacion de la imagen con la ventana y el tamano
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
//		Mete la imagen en la ventana
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	
	mlx_terminate(game.mlx);
	return (0);
}
