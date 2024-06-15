/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:43:11 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 15:10:21 by bbogdano         ###   ########.fr       */
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

void	validate_map(t_game *game)
{
	int	total_collectibles;

	validate_walls(game);
	check_rectangular(game);
	total_collectibles = validate_elements(game);
	validate_accessibility(game, total_collectibles);
}
