/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:50:12 by diespino          #+#    #+#             */
/*   Updated: 2026/01/13 16:30:45 by diespino         ###   ########.fr       */
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
	map[0] = "   111111111111111";
	map[1] = "   100000000000001";
	map[2] = "   100000000011111";
	map[3] = "   100000000000001";
	map[4] = "111100000000000001";
	map[5] = "100000000011101111";
	map[6] = "100000000000001";
	map[7] = "100011110000001";
	map[8] = "10001  10000001";
	map[9] = "11111  11111111";
	map[10] = NULL;
	return (map);
}

static void	pixel_put(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	mlx_put_pixel(game->img, x, y, color);
//	mete pixeles en imagen 
}

void	clear_img(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			pixel_put(game, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

// Dibujo de cuadrados (bloques de mapa y player)
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
		pixel_put(game, x + i++, y + size, 0xFFFFFFFF);// Sur [WHITE]
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

// Si en el mapa hay un 1 no se dibuja el POV del player
bool	touch(double ray_x, double ray_y, t_game *game)
{
	int	x;
	int	y;

	x = (int)(ray_x / BLOCK);
	y = (int)(ray_y / BLOCK);

	if (y < 0 || x < 0 || !game->map[y] || !game->map[y][x])
		return (true);
	return (game->map[y][x] == '1');
}

void	draw_line(t_player *player, t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	cos_angle;
	double	sin_angle;

	ray_x = player->x;// PLAYER X
	ray_y = player->y;// PLAYER Y
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
//		Calculo del angulo del POV
	while (!touch(ray_x, ray_y, game))
	{
		pixel_put(game, (int)ray_x, (int)ray_y, 0xFF0000FF);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
//		Printeo del cono de vision linea por linea
}

static void	draw_loop(void *param)
{
	t_game		*game;
	t_player	*player;
	double		fraction;
	double		ray_angle;
	int		i;

	game = (t_game *)param;
	player = &game->player;
//
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
//
	move_player(game->mlx, player);
// 		Calcula el movimiento del player segun lo inputs de las teclas
	clear_img(game);// Textura suelo/techo ??
//		Refresca la imagen para que no haya estela del movimiento del player
	draw_square((int)player->x, (int)player->y, 10, game);
//      	draw_square(player_x, player_y, size lado, game);
	draw_map(game);
//		Dibuja mapa
	fraction = (PI / 3.0) / (double)WIDTH;
	ray_angle = player->angle - (PI / 6.0);
//		Cacula POV del player (cuantas lineas para forar el cono)
	i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, ray_angle);
		ray_angle += fraction;
		i++;
	}
//		Printea el cono de vision
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
