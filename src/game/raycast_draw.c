/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:24:48 by diespino          #+#    #+#             */
/*   Updated: 2026/04/15 15:26:34 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_texture(t_game *game, int side, char block)
{
	if (block == 'D' && game->tex_door)
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

static void	init_texdata(t_texdata *td, double wall_x,
		t_proj *proj, t_game *game)
{
	td->tex_x = (int)(wall_x * (double)td->tex->width);
	if ((proj->side == 0 && game->rcast.ray_x < 0)
		|| (proj->side == 1 && game->rcast.ray_y < 0))
		td->tex_x = td->tex->width - td->tex_x - 1;
	td->step = (double)td->tex->height / proj->height;
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

static void	draw_col_pixels(t_game *game, t_texdata *td,
		t_proj *proj, int screen_x)
{
	uint32_t	color;
	int			y;

	y = proj->start_y;
	if (proj->start_y < 0)
		y = 0;
	while (y < proj->end_y && y < HEIGHT)
	{
		td->tex_y = (int)td->tex_pos & (td->tex->height - 1);
		td->tex_pos += td->step;
		color = reorder_color(((uint32_t *)td->tex->pixels)[td->tex_y
				* td->tex->width + td->tex_x]);
		pixel_put(game, screen_x, y, color);
		y++;
	}
}

void	draw_col(t_col *col, t_game *game)
{
	t_texdata	td;
	t_proj		proj;

	td.tex = get_texture(game, col->side, col->block);
	proj.height = (BLOCK / col->dist) * ((WIDTH / 2.0) / tan(PI / 6.0));
	proj.start_y = (int)((HEIGHT - proj.height) / 2.0);
	proj.end_y = (int)(proj.start_y + proj.height);
	proj.side = col->side;
	init_texdata(&td, col->wall_x, &proj, game);
	draw_col_pixels(game, &td, &proj, col->screen_x);
}
