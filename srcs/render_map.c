/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:10:30 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 18:53:43 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * 64, y * 64);
}

void	render_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				put_image(game, &game->wall, x, y);
			else if (game->map[y][x] == 'C')
				put_image(game, &game->coll, x, y);
			else if (game->map[y][x] == 'E')
				put_image(game, &game->door_c, x, y);
			else if (game->map[y][x] == 'P')
				put_image(game, &game->player.idle[0], x, y);
			else
				put_image(game, &game->bg, x, y);
			x++;
		}
		y++;
	}
}
