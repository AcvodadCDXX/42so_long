/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:10:30 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 21:42:45 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * 64, y * 64);
}

void	render_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)game->map_height)
	{
		x = 0;
		while (x < (int)game->map_width)
		{
			put_image(game, &game->bg, x, y);
			if (game->map[y][x] == '1')
				put_image(game, &game->wall, x, y);
			else if (game->map[y][x] == 'C')
				put_image(game, &game->coll, x, y);
			else if (game->map[y][x] == 'E' && game->collected < game->total_coll)
				put_image(game, &game->door_c, x, y);
			else if (game->map[y][x] == 'E' && game->collected >= game->total_coll)
				put_image(game, &game->door_o, x, y);
			x++;
		}
		y++;
	}
}

void render_player_idle(t_game *game)
{
    if (game->last_key == 97)  // 'A' key for facing left
        put_image(game, &game->player.idle[game->anim_frame], game->player.x, game->player.y);
    else  // Default to facing right if not left
        put_image(game, &game->player.idle[game->anim_frame + 6], game->player.x, game->player.y);
}

void render_player_run(t_game *game, char direction, char src_or_dst)
{
    int frame_offset = game->anim_frame % 6;  // Cycle through 6 frames

    if (direction == 'D')
    {
        if (src_or_dst == 'src')
        {
            if (game->last_key == 97)  // 'A' key for facing left
                put_image(game, &game->player.run[0 + frame_offset], game->player.x, game->player.y);
            else  // Default to facing right if not left
                put_image(game, &game->player.run[6 + frame_offset], game->player.x, game->player.y);
        }
        else
        {
            if (game->last_key == 97)
                put_image(game, &game->player.run[12 + frame_offset], game->player.x, game->player.y);
            else
                put_image(game, &game->player.run[18 + frame_offset], game->player.x, game->player.y);
        }
    }
    else if (direction == 'U')
    {
        if (src_or_dst == 'src')
        {
            if (game->last_key == 97)
                put_image(game, &game->player.run[24 + frame_offset], game->player.x, game->player.y);
            else
                put_image(game, &game->player.run[30 + frame_offset], game->player.x, game->player.y);
        }
        else
        {
            if (game->last_key == 97)
                put_image(game, &game->player.run[36 + frame_offset], game->player.x, game->player.y);
            else
                put_image(game, &game->player.run[42 + frame_offset], game->player.x, game->player.y);
        }
    }
    else if (direction == 'L')
    {
        if (src_or_dst == 'src')
            put_image(game, &game->player.run[48 + frame_offset], game->player.x, game->player.y);
        else
            put_image(game, &game->player.run[54 + frame_offset], game->player.x, game->player.y);
    }
    else if (direction == 'R')
    {
        if (src_or_dst == 'src')
            put_image(game, &game->player.run[60 + frame_offset], game->player.x, game->player.y);
        else
            put_image(game, &game->player.run[66 + frame_offset], game->player.x, game->player.y);
    }
}


void render_map(t_game *game)
{
    render_background(game);
    if (game->is_running)
    {
        // Example values, update based on actual game logic
        char direction = 'L';  // 'L' for left, 'R' for right, 'U' for up, 'D' for down
        char src_or_dst = 'src';  // 'src' for source, 'dst' for destination

        render_player_run(game, direction, src_or_dst);
    }
    render_player_idle(game);
}