/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:49 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/08 02:32:47 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**allocate_map(int fd, size_t *rows, size_t *cols)
{
	char	*line;
	char	**map;
	size_t	row;
	size_t	old_size;

	map = NULL;
	row = 0;
	old_size = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (row == 0)
			*cols = ft_strlen(line);
		if (ft_strlen(line) != *cols)
			handle_error("Error: Map is not rectangular.");
		map = ft_realloc(map, old_size, sizeof(char *) * (row + 2));
		old_size = sizeof(char *) * (row + 2);
		map[row] = line;
		row++;
	}
	map[row] = NULL;
	*rows = row;
	return (map);
}

char	**read_map(const char *filename, size_t *rows, size_t *cols)
{
	int		fd;
	char	**map;

	check_file(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Error: Failed to open map file.");
	map = allocate_map(fd, rows, cols);
	close(fd);
	return (map);
}

static void count_elements(char **map, size_t rows, size_t cols, t_elements *elems)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == 'P')
				elems->start_count++;
			else if (map[y][x] == 'E')
				elems->exit_count++;
			else if (map[y][x] == 'C')
				elems->collect_count++;
			else if (map[y][x] != '0' && map[y][x] != '1')
				handle_error("Error: Invalid character in map.");
			x++;
		}
		y++;
	}
}

void	validate_map_elements(char **map, size_t rows, size_t cols)
{
	t_elements elems = {0, 0, 0};

	count_elements(map, rows, cols, &elems);
	if (elems.start_count != 1 || elems.exit_count != 1 || elems.collect_count < 1)
		handle_error("Error: Invalid number of key elements in map.");
}

void	validate_walls(char **map, size_t rows, size_t cols)
{
	size_t		i;

	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			handle_error("Error: Map is not enclosed by walls.");
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			handle_error("Error: Map is not enclosed by walls.");
		i++;
	}
}
