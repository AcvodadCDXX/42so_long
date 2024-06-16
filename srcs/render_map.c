/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:10:30 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/16 22:27:52 by bbogdano         ###   ########.fr       */
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
			else if (game->map[y][x] == 'X')
				put_image(game, &game->trap, x, y);
			x++;
		}
		y++;
	}
}

void render_player_idle(t_game *game)
{
    int frame_offset = game->anim_frame % 6;  // Cycle through 6 frames

    if (game->last_key == 97)  // 'A' key for facing left
    {
        put_image(game, &game->player.idle[frame_offset], game->player.x, game->player.y);
    }
    else  // Default to facing right if not left
    {
        put_image(game, &game->player.idle[frame_offset + 6], game->player.x, game->player.y);
    }
}

void render_player_run(t_game *game)
{
    int frame_offset = game->anim_frame % 6;  // Cycle through 6 frames

    if (game->run_direction == 'L')
    {
        put_image(game, &game->player.run[48 + frame_offset], game->player.x, game->player.y);
        put_image(game, &game->player.run[54 + frame_offset], game->player.x - 1, game->player.y);
    }
    else if (game->run_direction == 'R')
    {
        put_image(game, &game->player.run[60 + frame_offset], game->player.x, game->player.y);
        put_image(game, &game->player.run[66 + frame_offset], game->player.x + 1, game->player.y);
    }
    else if (game->run_direction == 'U')
    {
        if (game->last_key == 97)
        {
            put_image(game, &game->player.run[24 + frame_offset], game->player.x, game->player.y);
            put_image(game, &game->player.run[36 + frame_offset], game->player.x, game->player.y - 1);
        }
        else
        {
            put_image(game, &game->player.run[30 + frame_offset], game->player.x, game->player.y);
            put_image(game, &game->player.run[42 + frame_offset], game->player.x, game->player.y - 1);
        }
    }
    else if (game->run_direction == 'D')
    {
        if (game->last_key == 97)
        {
            put_image(game, &game->player.run[0 + frame_offset], game->player.x, game->player.y);
            put_image(game, &game->player.run[12 + frame_offset], game->player.x, game->player.y + 1);
        }
        else
        {
            put_image(game, &game->player.run[6 + frame_offset], game->player.x, game->player.y);
            put_image(game, &game->player.run[18 + frame_offset], game->player.x, game->player.y + 1);
        }
    }

    if (frame_offset == 5)  // Last frame of the run animation
    {
        game->player.x = game->player.future_x;
        game->player.y = game->player.future_y;
        game->anim_frame = 0;  // Reset animation frame for the next animation

        if (game->player.is_eating)
        {
            transition_to_eat(game);  // Transition to eating animation
        }
		else if (game->player.is_taking_damage)
        {
            game->hp--;  // Reduce player health
            game->map[game->player.y][game->player.x] = '0';  // Mark the trap tile as empty
            if (game->hp <= 0)
            {
                game->player.is_dying = 1;  // Start death animation
            }
            game->is_running = 0;  // Stop running animation
            game->anim_frame = 0;  // Reset animation frame for the damage animation
        }
        else
        {
            game->is_running = 0;  // Stop running animation
        }
    }
}

void render_player_damage(t_game *game)
{
    int frame_offset = game->anim_frame % 4;  // Cycle through 4 frames

    if (game->last_key == 97)  // 'A' key for facing left
    {
        put_image(game, &game->player.dmg[frame_offset], game->player.x, game->player.y);
    }
    else  // Default to facing right if not left
    {
        put_image(game, &game->player.dmg[frame_offset + 4], game->player.x, game->player.y);
    }

    if (frame_offset == 3)  // Last frame of the damage animation
    {
        printf("Player took damage at (%d, %d)\n", game->player.x, game->player.y);
        game->player.is_taking_damage = 0;  // Stop damage animation
        game->anim_frame = 0;  // Reset animation frame for the next animation
    }
}

void render_player_death(t_game *game)
{
    int frame_offset = game->anim_frame % 6;  // Cycle through 6 frames

    if (game->last_key == 97)  // 'A' key for facing left
    {
        put_image(game, &game->player.die[frame_offset], game->player.x, game->player.y);
    }
    else  // Default to facing right if not left
    {
        put_image(game, &game->player.die[frame_offset + 6], game->player.x, game->player.y);
    }

    if (frame_offset == 5)  // Last frame of the death animation
    {
        printf("Player died at (%d, %d)\n", game->player.x, game->player.y);
        handle_error("You lose!");  // Print you lose and close the game
    }
}

void render_player_eat(t_game *game)
{
    int frame_offset = game->anim_frame % 5;  // Cycle through 5 frames

    if (game->last_key == 97)  // 'A' key for facing left
    {
        put_image(game, &game->player.eat[frame_offset], game->player.x, game->player.y);
    }
    else  // Default to facing right if not left
    {
        put_image(game, &game->player.eat[frame_offset + 5], game->player.x, game->player.y);
    }

    if (frame_offset == 4)  // Last frame of the eat animation
    {
        printf("Collectible picked up at (%d, %d)\n", game->player.x, game->player.y);
        game->player.is_eating = 0;  // Stop eating animation
        game->anim_frame = 0;  // Reset animation frame for the next animation
    }
}

void transition_to_eat(t_game *game)
{
    game->map[game->player.y][game->player.x] = '0';  // Mark the tile as empty
    game->collected++;  // Update collected items
    game->is_running = 0;  // Stop running animation
    game->player.is_eating = 1;  // Start eating animation
    game->anim_frame = 0;  // Reset animation frame for eating animation
}

void render_map(t_game *game)
{
    render_background(game);

    if (game->player.is_dying)
        render_player_death(game);
    else if (game->player.is_taking_damage)
        render_player_damage(game);
    else if (game->player.is_eating)
        render_player_eat(game);
    else if (game->is_running)
        render_player_run(game);
    else
        render_player_idle(game);
}