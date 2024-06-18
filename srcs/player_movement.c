/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 00:03:53 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 14:34:07 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_movement(int keycode, t_game *game)
{
	if (keycode == 119)
	{
		game->player.future_y--;
		game->run_direction = 'U';
	}
	else if (keycode == 97)
	{
		game->player.future_x--;
		game->run_direction = 'L';
	}
	else if (keycode == 115)
	{
		game->player.future_y++;
		game->run_direction = 'D';
	}
	else if (keycode == 100)
	{
		game->player.future_x++;
		game->run_direction = 'R';
	}
}

int	is_valid_move(t_game *game)
{
	if (game->player.future_x < 0 || game->player.future_y < 0 || \
		game->player.future_x >= (int)game->map_width || \
		game->player.future_y >= (int)game->map_height || \
		game->map[game->player.future_y][game->player.future_x] == '1')
		return (0);
	if (game->map[game->player.future_y][game->player.future_x] == 'E' \
		&& game->collected < game->total_coll)
		return (0);
	return (1);
}

void	set_player_state(t_game *game)
{
	if (game->map[game->player.future_y][game->player.future_x] == 'C')
	{
		game->map[game->player.future_y][game->player.future_x] = '0';
		if (game->player.hp < 2)
			game->player.hp++;
		game->player.state = EAT;
	}
	else if (game->map[game->player.future_y][game->player.future_x] == 'X')
	{
		game->player.hp--;
		if (game->player.hp <= 0)
			game->player.state = DIE;
		else
		{
			game->map[game->player.future_y][game->player.future_x] = '0';
			game->player.state = DMG;
		}
	}
	else if (game->map[game->player.future_y][game->player.future_x] == 'E' \
		&& game->collected >= game->total_coll)
		handle_victory(game);
	else
		game->player.state = RUN;
}
