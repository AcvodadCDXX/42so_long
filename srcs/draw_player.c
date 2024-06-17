/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banewsl <banewsl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 00:19:46 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/17 20:02:53 by banewsl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player_damage(t_game *game)
{
	int	frame_offset;

	frame_offset = game->anim_frame % 4;
	if (game->last_key == 97)
		put_image(game, &game->player.dmg[frame_offset], \
			game->player.x, game->player.y);
	else
		put_image(game, &game->player.dmg[frame_offset + 4], \
			game->player.x, game->player.y);
	if (frame_offset == 3)
	{
		printf("Player took damage at (%d, %d)\n", \
			game->player.x, game->player.y);
		game->map[game->player.y][game->player.x] = '0';
		if (game->player.hp <= 0)
			game->player.state = DIE;
		else
			game->player.state = IDLE;
		game->anim_frame = 0;
	}
}

void	draw_player_death(t_game *game)
{
	int	frame_offset;

	frame_offset = game->anim_frame % 6;
	if (game->last_key == 97)
		put_image(game, &game->player.die[frame_offset], \
			game->player.x, game->player.y);
	else
		put_image(game, &game->player.die[frame_offset + 6], \
			game->player.x, game->player.y);
	if (frame_offset == 5)
	{
		printf("Player died at (%d, %d)\n", game->player.x, game->player.y);
		handle_error("You lose!");
	}
}

void	draw_player_eat(t_game *game)
{
	int	frame_offset;

	frame_offset = game->anim_frame % 5;
	if (game->last_key == 97)
		put_image(game, &game->player.eat[frame_offset], \
			game->player.x, game->player.y);
	else
		put_image(game, &game->player.eat[frame_offset + 5], \
			game->player.x, game->player.y);
	if (frame_offset == 4)
	{
		printf("Collectible picked up at (%d, %d)\n", \
			game->player.x, game->player.y);
		game->map[game->player.y][game->player.x] = '0';
		game->collected++;
		game->player.state = IDLE;
		game->anim_frame = 0;
	}
}

void	draw_player_run(t_game *game)
{
	int	frame_offset;

	frame_offset = game->anim_frame % 6;
	if (game->run_direction == 'L')
		draw_run_left(game, frame_offset);
	else if (game->run_direction == 'R')
		draw_run_right(game, frame_offset);
	else if (game->run_direction == 'U')
		draw_run_up(game, frame_offset);
	else if (game->run_direction == 'D')
		draw_run_down(game, frame_offset);
	if (frame_offset == 5)
		handle_post_run_animation(game);
}
