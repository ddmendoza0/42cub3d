/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:26:35 by diespino          #+#    #+#             */
/*   Updated: 2026/04/09 15:56:35 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_door_texture(t_game *game, int side)
{
	if (game->tex_door)
		return (game->tex_door);
	if (side == 0)
	{
		if (game->rcast.ray_x > 0)
			return (game->tex_east);
		return (game->tex_west);
	}
	if (game->rcast.ray_y > 0)
		return (game->tex_south);
	return (game->tex_north);
}

static mlx_texture_t	*get_wall_texture(t_game *game, int side)
{
	if (side == 0)
	{
		if (game->rcast.ray_x > 0)
			return (game->tex_east);
		return (game->tex_west);
	}
	if (game->rcast.ray_y > 0)
		return (game->tex_south);
	return (game->tex_north);
}

static void	init_texdata(t_texdata *td, mlx_texture_t *tex,
			double wall_x, t_proj *proj, t_game *game)
{
	td->tex_x = (int)(wall_x * (double)tex->width);
	if ((proj->side == 0 && game->rcast.ray_x < 0)
		|| (proj->side == 1 && game->rcast.ray_y < 0))
		td->tex_x = tex->width - td->tex_x - 1;
	td->step = (double)tex->height / proj->height;
	td->tex_pos = (proj->start_y - HEIGHT
			/ 2.0 + proj->height / 2.0) * td->step;
	if (proj->start_y < 0)
		td->tex_pos += (-proj->start_y) * td->step;
}

static uint32_t	reorder_color(uint32_t raw)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (raw >> 24) & 0xFF;
	g = (raw >> 16) & 0xFF;
	b = (raw >> 8) & 0xFF;
	a = (raw) & 0xFF;
	return ((a << 24) | (b << 16) | (g << 8) | r);
}

void	draw_col(double dist, int screen_x, int side,
		double wall_x, char block, t_game *game)
{
	mlx_texture_t	*texture;
	t_texdata		td;
	t_proj			proj;
	uint32_t		color;
	int				y;

	if (block == 'D')
		texture = get_door_texture(game, side);
	else
		texture = get_wall_texture(game, side);
	proj.height = (BLOCK / dist) * ((WIDTH / 2.0) / tan(PI / 6.0));
	proj.start_y = (int)((HEIGHT - proj.height) / 2.0);
	proj.end_y = (int)(proj.start_y + proj.height);
	proj.side = side;
	init_texdata(&td, texture, wall_x, &proj, game);
	if (proj.start_y < 0)
		y = 0;
	else
		y = proj.start_y;
	while (y < proj.end_y && y < HEIGHT)
	{
		td.tex_y = (int)td.tex_pos & (texture->height - 1);
		td.tex_pos += td.step;
		color = reorder_color(((uint32_t *)texture->pixels)[td.tex_y
				* texture->width + td.tex_x]);
		pixel_put(game, screen_x, y, color);
		y++;
	}
}

double	grid_dist(t_game *game, int side, double ray_angle)
{
	double	dist;

	if (side == 0)
		dist = ((game->rcast.map_x - game->player.x / BLOCK
					+ (1 - game->rcast.step_x) / 2.0)
				* BLOCK / game->rcast.ray_x);
	else
		dist = ((game->rcast.map_y - game->player.y / BLOCK
					+ (1 - game->rcast.step_y) / 2.0)
				* BLOCK / game->rcast.ray_y);
	dist *= cos(ray_angle - game->player.angle);
	return (dist);
}

static int	grid_move(t_game *game)
{
	bool	hit;
	int		side;

	hit = false;
	while (!hit)
	{
		if (game->rcast.side_dist_x < game->rcast.side_dist_y)
		{
			game->rcast.side_dist_x += game->rcast.dist_x;
			game->rcast.map_x += game->rcast.step_x;
			side = 0;
		}
		else
		{
			game->rcast.side_dist_y += game->rcast.dist_y;
			game->rcast.map_y += game->rcast.step_y;
			side = 1;
		}
		if (game->map.grid[game->rcast.map_y][game->rcast.map_x] == '1' ||
			game->map.grid[game->rcast.map_y][game->rcast.map_x] == 'D')
			hit = true;
	}
	return (side);
}

static void	grid_pos_init(t_game *game)
{
	if (game->rcast.ray_x < 0)
	{
		game->rcast.step_x = -1;
		game->rcast.side_dist_x = (game->player.x - game->rcast.map_x
				* BLOCK) / fabs(game->rcast.ray_x);
	}
	else
	{
		game->rcast.step_x = 1;
		game->rcast.side_dist_x = ((game->rcast.map_x + 1)
				* BLOCK - game->player.x) / fabs(game->rcast.ray_x);
	}
	if (game->rcast.ray_y < 0)
	{
		game->rcast.step_y = -1;
		game->rcast.side_dist_y = (game->player.y - game->rcast.map_y
				* BLOCK) / fabs(game->rcast.ray_y);
	}
	else
	{
		game->rcast.step_y = 1;
		game->rcast.side_dist_y = ((game->rcast.map_y + 1)
				* BLOCK - game->player.y) / fabs(game->rcast.ray_y);
	}
}

void	draw_line(t_game *game, double ray_angle, int screen_x)
{
	int		side;
	double	dist;
	double	wall_x;
	char	block;

	game->rcast.map_x = (int)(game->player.x / BLOCK);
	game->rcast.map_y = (int)(game->player.y / BLOCK);
	game->rcast.ray_x = cos(ray_angle);
	game->rcast.ray_y = sin(ray_angle);
	game->rcast.dist_x = fabs(BLOCK / game->rcast.ray_x);
	game->rcast.dist_y = fabs(BLOCK / game->rcast.ray_y);
	grid_pos_init(game);
	side = grid_move(game);
	dist = grid_dist(game, side, ray_angle);
	block = game->map.grid[game->rcast.map_y][game->rcast.map_x];
	if (side == 0)
		wall_x = game->player.y + dist * game->rcast.ray_y;
	else
		wall_x = game->player.x + dist * game->rcast.ray_x;
	wall_x = wall_x / BLOCK;
	wall_x -= floor(wall_x);
	draw_col(dist, screen_x, side, wall_x, block, game);
}
