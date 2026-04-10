/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:23:43 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:38:56 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_to_value(char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	return (line);
}

static void	assign_color(t_colors *colors, int is_floor, int rgb[3])
{
	if (is_floor)
	{
		colors->floor_r = rgb[0];
		colors->floor_g = rgb[1];
		colors->floor_b = rgb[2];
	}
	else
	{
		colors->ceiling_r = rgb[0];
		colors->ceiling_g = rgb[1];
		colors->ceiling_b = rgb[2];
	}
}

int	parse_color(char *line, t_colors *colors, int is_floor)
{
	char	**rgb;
	int		argb[3];

	line = skip_to_value(line);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (printf("Error\nRGB must have exactly 3 values\n"), 0);
	if (!validate_rgb_count(rgb))
		return (0);
	if (!validate_rgb_range(rgb, &argb[0], &argb[1], &argb[2]))
		return (0);
	assign_color(colors, is_floor, argb);
	free_rgb_array(rgb);
	return (1);
}
