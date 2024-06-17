/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banewsl <banewsl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:53:48 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/17 21:05:47 by banewsl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
		update_player_position(keycode, game);
	if (keycode == 97 || keycode == 100)
		game->last_key = keycode;
	return (0);
}

int	game_loop(t_game *game)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - game->last_update_time.tv_sec) \
	* 1000 + (current_time.tv_usec - game->last_update_time.tv_usec) / 1000;
	if (elapsed_time >= 100)
	{
		game->anim_frame++;
		draw_map(game);
		draw_hud(game);
		game->last_update_time = current_time;
	}
	return (0);
}

void	update_player_position(int keycode, t_game *game)
{
	if (game->is_running || game->player.state == EAT || \
		game->player.state == DIE || game->player.state == DMG)
		return ;
	game->player.future_x = game->player.x;
	game->player.future_y = game->player.y;
	handle_movement(keycode, game);
	if (!is_valid_move(game))
		return ;
	game->is_running = 1;
	game->anim_frame = 0;
	set_player_state(game);
	game->player.move_count++;
}
