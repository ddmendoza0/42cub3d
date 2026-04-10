/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendoza <dmendoza@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:29 by dmendoza          #+#    #+#             */
/*   Updated: 2026/03/13 10:30:05 by dmendoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c =='D');
}


static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_char(game->map.grid[i][j]))
				return (printf("Error\nInvalid character in map: %c (ASCII: %d)\n", game->map.grid[i][j], game->map.grid[i][j]), 0);
			if (is_player(game->map.grid[i][j]))
			{
				player_count++;
				game->player.x = j;
				game->player.y = i;
				game->player.orientation = game->map.grid[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("Error\nMap must have exactly one player\n"), 0);
	return (1);
}

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		copy[i] = ft_strdup(game->map.grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_map_copy(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	is_valid_position(char **map, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0)
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	return (1);
}

static int	push_neighbors(t_point *stack, int *top, t_point cur)
{
	int	dirs[4][2];
	int	i;

	dirs[0][0] = 1;  dirs[0][1] = 0;
	dirs[1][0] = -1; dirs[1][1] = 0;
	dirs[2][0] = 0;  dirs[2][1] = 1;
	dirs[3][0] = 0;  dirs[3][1] = -1;
	i = 0;
	while (i < 4)
	{
		stack[*top].x = cur.x + dirs[i][0];
		stack[*top].y = cur.y + dirs[i][1];
		(*top)++;
		i++;
	}
	return (1);
}

static int	process_cell(char **map, t_point cur, t_game *game,
				t_point *stack, int *top)
{
	if (!is_valid_position(map, cur.x, cur.y, game))
		return (0);
	if (map[cur.y][cur.x] == '1' || map[cur.y][cur.x] == 'X')
		return (1);
	if (map[cur.y][cur.x] == ' ')
		return (0);
	if (cur.x == 0 || cur.y == 0 || cur.y == game->map.height - 1)
		return (0);
	map[cur.y][cur.x] = 'X';
	push_neighbors(stack, top, cur);
	return (1);
}

static int	flood_fill(char **map, int start_x, int start_y, t_game *game)
{
	t_point	*stack;
	t_point	cur;
	int		top;
	int		max;
	int		result;

	max = game->map.width * game->map.height;
	stack = malloc(sizeof(t_point) * max);
	if (!stack)
		return (0);
	top = 0;
	stack[top].x = start_x;
	stack[top].y = start_y;
	top++;
	result = 1;
	while (top > 0 && result)
	{
		top--;
		cur = stack[top];
		result = process_cell(map, cur, game, stack, &top);
	}
	free(stack);
	return (result);
}

int	validate_map_closed(t_game *game)
{
	char	**map_copy;
	int		result;

	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	result = flood_fill(map_copy, (int)game->player.x, (int)game->player.y, game);
	free_map_copy(map_copy, game->map.height);
	if (!result)
		return (printf("Error\nMap is not closed by walls\n"), 0);
	return (1);
}
