/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:04:32 by banewsl           #+#    #+#             */
/*   Updated: 2024/06/18 09:29:05 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_hud(t_game *game)
{
    char move_str[4];
    int x_offset;
    int y_offset = 0;  // Offset from the top

    // Format move count as a 3-digit number
    snprintf(move_str, sizeof(move_str), "%03d", game->player.move_count);

    // Draw move counter in the top left corner
    mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, move_str);

    // Calculate x_offset for hearts based on window width
    x_offset = (game->map_width - 1) * game->tile_size; // Place heart in top-right corner

    // Debugging prints
    printf("Map width: %lu, Tile size: %lu\n", game->map_width, game->tile_size);
    printf("Calculated x_offset: %d\n", x_offset);

    // Draw hearts based on player's health
    if (game->player.hp == 2)
    {
        mlx_put_image_to_window(game->mlx, game->win, game->heart.img, x_offset, y_offset);
        printf("Drawing full heart at (%d, %d)\n", x_offset, y_offset);
    }
    else if (game->player.hp == 1)
    {
        mlx_put_image_to_window(game->mlx, game->win, game->heart_half.img, x_offset, y_offset);
        printf("Drawing half heart at (%d, %d)\n", x_offset, y_offset);
    }
    else
    {
        printf("Player has no hearts to draw\n");
    }
}
