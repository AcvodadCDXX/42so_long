/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:04:32 by banewsl           #+#    #+#             */
/*   Updated: 2024/06/18 15:08:18 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_hud(t_game *game)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	y_offset = 0;
	if (game->player.hp == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->heart.img, \
	x_offset, y_offset);
	else if (game->player.hp == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->heart_half.img, \
	x_offset, y_offset);
}

