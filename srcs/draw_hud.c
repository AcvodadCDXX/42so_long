/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:04:32 by banewsl           #+#    #+#             */
/*   Updated: 2024/06/18 11:31:48 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_hud(t_game *game)
{
	char	move_str[4];
	int		x_offset;
	int		y_offset;

	y_offset = 0;
	snprintf(move_str, sizeof(move_str), "%03d", game->player.move_count);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, move_str);
	x_offset = (game->map_width - 1) * game->tile_size;
	if (game->player.hp == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->heart.img, \
		x_offset, y_offset);
	else if (game->player.hp == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->heart_half.img, \
		x_offset, y_offset);
}
