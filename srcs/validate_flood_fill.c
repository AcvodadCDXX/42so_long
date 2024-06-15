/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flood_fill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:44:36 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 15:24:47 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int x, int y, t_flood_fill_state *state)
{
	if (x < 0 || y < 0 || !map[y] \
		|| map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'E')
		return ;
	if (map[y][x] == 'C')
		state->collectibles_found++;
	if (map[y][x] == 'E')
		state->exit_found++;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, state);
	flood_fill(map, x - 1, y, state);
	flood_fill(map, x, y + 1, state);
	flood_fill(map, x, y - 1, state);
}

static void	find_start_position(t_game *game, int *start_x, int *start_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)game->map_height)
	{
		j = 0;
		while (j < (int)game->map_width)
		{
			if (game->map[i][j] == 'P')
			{
				*start_x = j;
				*start_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	handle_error("Error: No start position found");
}

static char	**copy_map(char **original, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		handle_error("Memory allocation failed for map copy");
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
			handle_error("Memory allocation failed for map copy");
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

void	validate_accessibility(t_game *game, int total_coll)
{
	char				**map_copy;
	t_flood_fill_state	state;
	int					start_x;
	int					start_y;

	find_start_position(game, &start_x, &start_y);
	map_copy = copy_map(game->map, game->map_height);
	state.collectibles_found = 0;
	state.exit_found = 0;
	flood_fill(map_copy, start_x, start_y, &state);
	free_map_copy(map_copy, game->map_height);
	if (state.collectibles_found != total_coll)
		handle_error("Error: Not all collectibles are accessible");
	if (state.exit_found == 0)
		handle_error("Error: Exit is not accessible");
}
