/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:04:32 by banewsl           #+#    #+#             */
/*   Updated: 2024/06/20 14:54:43 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_hud(t_game *game)
{
	int		x_offset;
	int		y_offset;
	char	move_count_str[20];

	x_offset = 0;
	y_offset = 0;
	if (game->player.hp == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->heart.img, \
	x_offset, y_offset);
	else if (game->player.hp == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->heart_half.img, \
	x_offset, y_offset);
	ft_snprintf(move_count_str, sizeof(move_count_str), \
	"Moves: %d", game->player.move_count);
	mlx_string_put(game->mlx, game->win, x_offset + 70, \
	y_offset + 32, 0x00FFFF, move_count_str);
}
