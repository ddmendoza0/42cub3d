#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

static char	**convert_list_to_array(t_list *map_lines, int height)
{
	char	**grid;
	int		i;
	t_list	*current;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	current = map_lines;
	i = 0;
	while (current)
	{
		grid[i] = ft_strdup((char *)current->content);
		if (!grid[i])
			return (NULL);
		if (grid[i][ft_strlen(grid[i]) - 1] == '\n')
			grid[i][ft_strlen(grid[i]) - 1] = '\0';
		current = current->next;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

int	parse_map(int fd, t_game *game)
{
	char	*line;
	t_list	*map_lines;
	t_list	*new_node;
	int		height;

	map_lines = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			new_node = ft_lstnew(line);
			if (!new_node)
				return (0);
			ft_lstadd_back(&map_lines, new_node);
			height++;
		}
		else if (line[0] != '\n' && map_lines != NULL)
		{
			free(line);
			return (printf("Error\nInvalid map format\n"), 0);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	game->map.grid = convert_list_to_array(map_lines, height);
	game->map.height = height;
	ft_lstclear(&map_lines, free);
	return (1);
}