/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:53:48 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 21:36:04 by bbogdano         ###   ########.fr       */
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
	if (keycode == 97 || keycode == 100)
		game->last_key = keycode;
	if (game->anim_frame != 0 && (game->last_key == 97 \
	|| game->last_key == 100))
		return (0);
	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
		update_player_position(keycode, game);
	return (0);
}

int	game_loop(t_game *game)
{
	game->timer++;
	if (game->timer % 5 == 0)
	{
		if (game->player.idle)
			game->anim_frame = (game->anim_frame + 1) % 6;
		render_map(game);
	}
	return (0);
}

void	update_player_position(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (keycode == 119)
		new_y--;
	else if (keycode == 97)
		new_x--;
	else if (keycode == 115)
		new_y++;
	else if (keycode == 100)
		new_x++;
	if (new_x < 0 || new_y < 0 || new_x >= (int)game->map_width || new_y >= (int)game->map_height || game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'T')
		handle_trap(game);
	else if (game->map[new_y][new_x] == 'C')
		handle_collectible(game, new_x, new_y);
	else if (game->map[new_y][new_x] == 'E' && game->collected >= game->total_coll)
		handle_exit(game);
	else
		move_player(game, new_x, new_y);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	game->player.x = new_x;
	game->player.y = new_y;
	if (game->last_key == 97)
		game->anim_frame = 0;
	else if (game->last_key == 100)
		game->anim_frame = 0;
}
