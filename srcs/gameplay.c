/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:53:48 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/16 21:11:40 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_handler(int keycode, t_game *game)
{
    if (keycode == 65307)  // ESC key code for closing the game
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }

    if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)  // W, A, S, D keys
    {
        update_player_position(keycode, game);
    }

    // Immediately handle idle animation direction change
    if (keycode == 97 || keycode == 100)  // 'A' or 'D' keys
    {
        game->last_key = keycode;
    }

    return (0);
}

int game_loop(t_game *game)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    long elapsed_time = (current_time.tv_sec - game->last_update_time.tv_sec) * 1000 + (current_time.tv_usec - game->last_update_time.tv_usec) / 1000;

    if (elapsed_time >= 100)  // 100 milliseconds = 0.1 second per frame
    {
        game->anim_frame++;
        render_map(game);
        game->last_update_time = current_time;
    }

    return (0);
}

void update_player_position(int keycode, t_game *game)
{
	if (game->is_running || game->player.is_eating || game->player.is_dying || game->player.is_taking_damage)
    return ;

    int new_x = game->player.x;
    int new_y = game->player.y;
    char direction;

    if (keycode == 119)  // W key
    {
        new_y--;
        direction = 'U';
    }
    else if (keycode == 97)  // A key
    {
        new_x--;
        direction = 'L';
    }
    else if (keycode == 115)  // S key
    {
        new_y++;
        direction = 'D';
    }
    else if (keycode == 100)  // D key
    {
        new_x++;
        direction = 'R';
    }

    if (new_x < 0 || new_y < 0 || new_x >= (int)game->map_width || new_y >= (int)game->map_height || game->map[new_y][new_x] == '1')
        return;
    if (game->map[new_y][new_x] == 'E' && game->collected < game->total_coll)
        return;

    game->is_running = 1;
    game->run_direction = direction;
    game->player.future_x = new_x;
    game->player.future_y = new_y;
	game->anim_frame = 0;
	if (game->map[new_y][new_x] == 'C')
    {
        game->player.is_eating = 1;
    }
	else if (game->map[new_y][new_x] == 'X')
    {
        game->player.is_taking_damage = 1;
    }
}

