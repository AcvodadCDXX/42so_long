/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:20:16 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 16:20:48 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*read_line(int fd)
{
	char	*line;
	char	*buffer;
	int		ret;
	int		len;

	buffer = malloc(1024);
	if (!buffer)
		return (NULL);
	line = NULL;
	len = 0;
	while ((ret = read(fd, buffer + len, 1)) > 0)
	{
		if (buffer[len] == '\n' || buffer[len] == '\0')
			break ;
		len++;
	}
	if (len > 0)
		line = ft_substr(buffer, 0, len);
	free(buffer);
	return (line);
}

static char	**allocate_map(size_t rows, size_t cols)
{
	char	**map;
	size_t	i;

	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
		handle_error("Error: Map allocation failed");
	i = 0;
	while (i < rows)
	{
		map[i] = malloc(sizeof(char) * (cols + 1));
		if (!map[i])
			handle_error("Error: Map row allocation failed");
		i++;
	}
	map[rows] = NULL;
	return (map);
}

static void	check_map_validity(char **map, size_t rows, size_t cols)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'C' &&
				map[i][j] != 'E' && map[i][j] != 'P')
				handle_error("Error: Invalid character in map");
			j++;
		}
		i++;
	}
}

char	**read_map(const char *filename, size_t *rows, size_t *cols)
{
	int		fd;
	char	*line;
	char	**map;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Error: Failed to open map file");
	*rows = 0;
	*cols = 0;
	while ((line = read_line(fd)))
	{
		if (*cols == 0)
			*cols = ft_strlen(line);
		(*rows)++;
		free(line);
	}
	close(fd);
	map = allocate_map(*rows, *cols);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Error: Failed to reopen map file");
	i = 0;
	while ((line = read_line(fd)))
	{
		ft_strlcpy(map[i], line, *cols + 1);
		free(line);
		i++;
	}
	close(fd);
	check_map_validity(map, *rows, *cols);
	return (map);
}
