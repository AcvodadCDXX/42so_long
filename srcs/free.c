/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:55:32 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/19 12:37:25 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_player(t_player *player, void *mlx)
{
    for (int i = 0; i < 12; i++) {
        if (player->idle[i].img) {
            mlx_destroy_image(mlx, player->idle[i].img);
        }
    }
    for (int i = 0; i < 72; i++) {
        if (player->run[i].img) {
            mlx_destroy_image(mlx, player->run[i].img);
        }
    }
    for (int i = 0; i < 8; i++) {
        if (player->dmg[i].img) {
            mlx_destroy_image(mlx, player->dmg[i].img);
        }
    }
    for (int i = 0; i < 12; i++) {
        if (player->die[i].img) {
            mlx_destroy_image(mlx, player->die[i].img);
        }
    }
    for (int i = 0; i < 10; i++) {
        if (player->eat[i].img) {
            mlx_destroy_image(mlx, player->eat[i].img);
        }
    }
}

void free_map(char **map, size_t height)
{
    if (map)
    {
        for (size_t i = 0; i < height; i++)
        {
            if (map[i])
                free(map[i]);
        }
        free(map);
    }
}

void free_images(t_game *game)
{
    if (game->mlx)
    {
        if (game->heart.img)
            mlx_destroy_image(game->mlx, game->heart.img);
        if (game->heart_half.img)
            mlx_destroy_image(game->mlx, game->heart_half.img);
        if (game->bg.img)
            mlx_destroy_image(game->mlx, game->bg.img);
        if (game->wall.img)
            mlx_destroy_image(game->mlx, game->wall.img);
        if (game->coll.img)
    		mlx_destroy_image(game->mlx, game->coll.img);
        if (game->trap.img)
            mlx_destroy_image(game->mlx, game->trap.img);
        if (game->door_c.img)
            mlx_destroy_image(game->mlx, game->door_c.img);
        if (game->door_o.img)
            mlx_destroy_image(game->mlx, game->door_o.img);
    }
}

void free_game(t_game *game)
{
    if (game)
	{
        free_player(&game->player, game->mlx);
        free_map(game->map, game->map_height);
        free_images(game);
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
        if (game->mlx) 
		{
            free(game->mlx);
            game->mlx = NULL;
        }
    }
}

//valgrind --leak-check=full --show-leak-kinds=all ./so_long example1.ber
