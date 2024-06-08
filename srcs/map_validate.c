/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:56:16 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/07 16:22:33 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	find_start(char **map, size_t rows, size_t cols)
{
	t_point	start;
	size_t		y;
	size_t		x;

	start = (t_point){-1, -1};
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == 'P')
				return ((t_point){x, y});
			x++;
		}
		y++;
	}
	return (start);
}

static void	check_reachable(char **map, size_t rows, size_t cols)
{
	size_t		y;
	size_t		x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				handle_error("Error: Not all collectibles or exit are reachable.");
			x++;
		}
		y++;
	}
}

void	validate_map(char **map, size_t rows, size_t cols)
{
	t_point	start;

	validate_walls(map, rows, cols);
	validate_map_elements(map, rows, cols);
	start = find_start(map, rows, cols);
	if (start.x == -1 || start.y == -1)
		handle_error("Error: No starting position found.");
	flood_fill(map, (t_point){cols, rows}, start);
	check_reachable(map, rows, cols);
}
