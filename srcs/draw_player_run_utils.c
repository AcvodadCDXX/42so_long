/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_run_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 00:53:00 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/19 12:43:42 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_run_left(t_game *game, int frame_offset)
{
	put_image(game, &game->player.run[48 + frame_offset], \
		game->player.x, game->player.y);
	put_image(game, &game->player.run[54 + frame_offset], \
		game->player.x - 1, game->player.y);
}

void	draw_run_right(t_game *game, int frame_offset)
{
	put_image(game, &game->player.run[60 + frame_offset], \
		game->player.x, game->player.y);
	put_image(game, &game->player.run[66 + frame_offset], \
		game->player.x + 1, game->player.y);
}

void	draw_run_up(t_game *game, int frame_offset)
{
	if (game->last_key == 97)
	{
		put_image(game, &game->player.run[24 + frame_offset], \
		game->player.x, game->player.y);
		put_image(game, &game->player.run[36 + frame_offset], \
		game->player.x, game->player.y - 1);
	}
	else
	{
		put_image(game, &game->player.run[30 + frame_offset], \
		game->player.x, game->player.y);
		put_image(game, &game->player.run[42 + frame_offset], \
		game->player.x, game->player.y - 1);
	}
}

void	draw_run_down(t_game *game, int frame_offset)
{
	if (game->last_key == 97)
	{
		put_image(game, &game->player.run[0 + frame_offset], \
			game->player.x, game->player.y);
		put_image(game, &game->player.run[12 + frame_offset], \
			game->player.x, game->player.y + 1);
	}
	else
	{
		put_image(game, &game->player.run[6 + frame_offset], \
			game->player.x, game->player.y);
		put_image(game, &game->player.run[18 + frame_offset], \
			game->player.x, game->player.y + 1);
	}
}

void	handle_post_run_animation(t_game *game)
{
	game->player.x = game->player.future_x;
	game->player.y = game->player.future_y;
	game->anim_frame = 0;
	if (game->player.state == EAT)
	{
		game->collected++;
		if (game->collected >= game->total_coll)
			game->map[game->player.y][game->player.x] = 'E';
	}
	else if (game->player.state == DMG)
	{
		if (game->player.hp <= 0)
		{
			game->player.state = DIE;
			close_handler(game);
			handle_error("You lose!");
		}
	}
	game->is_running = 0;
	game->player.state = IDLE;
}
