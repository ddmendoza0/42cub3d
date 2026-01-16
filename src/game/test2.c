/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:50:12 by diespino          #+#    #+#             */
/*   Updated: 2026/01/16 17:12:11 by diespino         ###   ########.fr       */
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
	map[5] = "100000000000101111";
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

double	distance(double x, double y)
{
	return (sqrt(x * x + y * y));
}

double	fixed_dist(double x1, double y1, double x2, double y2, t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	angle;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	return (distance(delta_x, delta_y) * cos(angle));
}

void	draw_line(t_player *player, t_game *game, double ray_angle, int screen_x)
{
	double	ray_x;
	double	ray_y;
	double	cos_angle;
	double	sin_angle;

	double	dist;
	double	height;
	int	start_y;
	int	end_y;

	double	prev_x;
	double	prev_y;
	int	map_x;
	int	map_y;
	int	prev_map_x;
	int	prev_map_y;
	int	wall_dir;
	int	color;

	ray_x = player->x;// PLAYER X
	ray_y = player->y;// PLAYER Y
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
//
	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			pixel_put(game, (int)ray_x, (int)ray_y, 0xFF0000FF);
		prev_x = ray_x;
		prev_y = ray_y;
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		map_x = (int)(ray_x / BLOCK);
		map_y = (int)(ray_y / BLOCK);
		prev_map_x = (int)(prev_x / BLOCK);
		prev_map_y = (int)(prev_y / BLOCK);
//
		if (map_x != prev_map_x)
		{
			if (cos_angle > 0)
				wall_dir = EAST;
			else
				wall_dir = WEST;
		}
		else
		{
			if (sin_angle > 0)
				wall_dir = SOUTH;
			else
				wall_dir = NORTH;
		}
		if (wall_dir == NORTH)
			color = 0x00FF00FF;// GREEN
		else if (wall_dir == WEST)
			color = 0xFF0000FF;// RED
		else if (wall_dir == EAST)
			color = 0x0000FFFF;// BLUE
		else if (wall_dir == SOUTH)
			color = 0x00FFFFFF;// YELLOW
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		height = (BLOCK / dist) * (WIDTH / 2.0);
		start_y = (int)((HEIGHT - height) / 2.0);
		end_y = (int)(start_y + height);
		if (start_y < 0)
			start_y = 0;
		if (end_y > HEIGHT)
			end_y = HEIGHT;
		while (start_y < end_y)
		{
			pixel_put(game, screen_x, start_y, color);
//			pixel_put(game, screen_x, start_y, 0xFF0000FF);
			start_y++;
		}
	}
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
//	move_player(game->mlx, player);
	move_player(game, player);
	clear_img(game);// Textura suelo/techo ??
//
	if (DEBUG)
	{
		draw_square((int)player->x, (int)player->y, 10, game);
		draw_map(game);
	}
//	
	fraction = (PI / 3.0) / (double)WIDTH;
	ray_angle = player->angle - (PI / 6.0);
//
	i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, ray_angle, i);
		ray_angle += fraction;
		i++;
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
