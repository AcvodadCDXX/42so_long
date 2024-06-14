/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:20:16 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 19:05:12 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	get_map_dimensions(char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		height;
	int		width;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open map file");
	height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (height == 0)
			width = ft_strlen(line);
		height++;
		free(line);
	}
	free(line);
	close(fd);
	game->map_width = width;
	game->map_height = height;
	return (1);
}

int	read_map(char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		row;

	if (!get_map_dimensions(file, game))
		handle_error("Failed to get map dimensions");
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		handle_error("Memory allocation failed for map");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open map file");
	row = 0;
	while (get_next_line(fd, &line) > 0)
	{
		game->map[row] = ft_strdup(line);
		free(line);
		row++;
	}
	free(line);
	game->map[row] = NULL;
	close(fd);
	return (1);
}