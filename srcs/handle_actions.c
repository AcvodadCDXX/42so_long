/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:16:53 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/16 16:35:38 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_trap(t_game *game)
{
	game->player.hp--;
	if (game->player.hp <= 0)
		handle_error("Game over: Player died");
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	game->collected++;
	game->map[new_y][new_x] = '0';
}

void	handle_exit(t_game *game)
{
	(void)game;
	handle_error("Congratulations! You won the game!");
}
