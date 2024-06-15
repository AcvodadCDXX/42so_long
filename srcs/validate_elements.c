/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:16:07 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 15:12:15 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	count_elements(t_game *game, int *exits, int *starts, int *coll)
{
	int	i;
	int	j;

	*exits = 0;
	*starts = 0;
	*coll = 0;
	i = 0;
	while (i < (int)game->map_height)
	{
		j = 0;
		while (j < (int)game->map_width)
		{
			if (game->map[i][j] == 'E')
				(*exits)++;
			else if (game->map[i][j] == 'P')
				(*starts)++;
			else if (game->map[i][j] == 'C')
				(*coll)++;
			j++;
		}
		i++;
	}
}

int	validate_elements(t_game *game)
{
	int	exits;
	int	starts;
	int	coll;

	count_elements(game, &exits, &starts, &coll);
	if (exits != 1)
		handle_error("Error: Map must contain exactly one exit");
	if (starts != 1)
		handle_error("Error: Map must contain exactly one start position");
	if (coll < 1)
		handle_error("Error: Map must contain at least one collectible");
	return (coll);
}
