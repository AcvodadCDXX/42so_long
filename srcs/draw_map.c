/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:10:30 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 09:19:50 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_element_image(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == '1')
		put_image(game, &game->wall, x, y);
	else if (tile == 'C')
		put_image(game, &game->coll, x, y);
	else if (tile == 'E')
	{
		if (game->collected < game->total_coll)
			put_image(game, &game->door_c, x, y);
		else
			put_image(game, &game->door_o, x, y);
	}
	else if (tile == 'X')
		put_image(game, &game->trap, x, y);
}

void	draw_background(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < (int)game->map_height)
	{
		x = 0;
		while (x < (int)game->map_width)
		{
			put_image(game, &game->bg, x, y);
			put_element_image(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_player_idle(t_game *game)
{
	int	frame_offset;

	frame_offset = game->anim_frame % 6;
	if (game->last_key == 97)
		put_image(game, &game->player.idle[frame_offset], \
		game->player.x, game->player.y);
	else
		put_image(game, &game->player.idle[frame_offset + 6], \
		game->player.x, game->player.y);
}

void	draw_map(t_game *game)
{
	draw_background(game);
	if (game->player.state == DIE)
		draw_player_death(game);
	else if (game->player.state == DMG)
		draw_player_damage(game);
	else if (game->player.state == EAT)
		draw_player_eat(game);
	else if (game->is_running)
		draw_player_run(game);
	else
		draw_player_idle(game);
}
