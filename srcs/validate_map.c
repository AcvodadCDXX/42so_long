/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:43:11 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/21 15:17:43 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < (int)game->map_width)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
			handle_error("Error: Map is not enclosed by walls");
		i++;
	}
	i = 0;
	while (i < (int)game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			handle_error("Error: Map is not enclosed by walls");
		i++;
	}
}

static void	check_rectangular(t_game *game)
{
	int		i;
	size_t	line_length;

	if (game->map_height == 0)
		handle_error("Error: Map is empty");
	line_length = ft_strlen(game->map[0]);
	if (line_length == 0)
		handle_error("Error: Map is empty");
	i = 1;
	while (i < (int)game->map_height)
	{
		if (ft_strlen(game->map[i]) != line_length)
			handle_error("Error: Map is not rectangular");
		i++;
	}
	game->map_width = line_length;
}

static void	check_map_size(t_game *game)
{
	size_t	max_map_width;
	size_t	max_map_height;

	max_map_width = 3840 / game->tile_size;
	max_map_height = 2160 / game->tile_size;
	if (game->map_width > max_map_width || game->map_height > max_map_height)
		handle_error("Map is too large for the screen resolution");
}

void	validate_map(t_game *game)
{
	int	total_collectibles;

	validate_walls(game);
	check_rectangular(game);
	check_map_size(game);
	total_collectibles = validate_elements(game);
	validate_accessibility(game, total_collectibles);
}
