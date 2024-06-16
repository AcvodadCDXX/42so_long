/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:53:48 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/16 17:00:35 by bbogdano         ###   ########.fr       */
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

int game_loop(t_game *game)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    long elapsed_time = (current_time.tv_sec - game->last_update_time.tv_sec) * 1000 + (current_time.tv_usec - game->last_update_time.tv_usec) / 1000;
    
    if (elapsed_time >= 100)  // 100 milliseconds = 0.1 second per frame
    {
        game->anim_frame = (game->anim_frame + 1) % 6;
        render_map(game);
        game->last_update_time = current_time;
    }

    return (0);
}

void update_player_position(int keycode, t_game *game)
{
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

    // Delay the position update to synchronize with the animation
    game->player.future_x = new_x;
    game->player.future_y = new_y;
}

