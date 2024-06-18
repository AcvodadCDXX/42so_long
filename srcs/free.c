/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:55:32 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 17:41:20 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_player(t_player *player, void *mlx) {
    for (int i = 0; i < 12; i++) {
        if (player->idle[i].img) {
            printf("Freeing idle image %d\n", i);
            mlx_destroy_image(mlx, player->idle[i].img);
            player->idle[i].img = NULL;
        }
    }
    for (int i = 0; i < 72; i++) {
        if (player->run[i].img) {
            printf("Freeing run image %d\n", i);
            mlx_destroy_image(mlx, player->run[i].img);
            player->run[i].img = NULL;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (player->dmg[i].img) {
            printf("Freeing dmg image %d\n", i);
            mlx_destroy_image(mlx, player->dmg[i].img);
            player->dmg[i].img = NULL;
        }
    }
    for (int i = 0; i < 12; i++) {
        if (player->die[i].img) {
            printf("Freeing die image %d\n", i);
            mlx_destroy_image(mlx, player->die[i].img);
            player->die[i].img = NULL;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (player->eat[i].img) {
            printf("Freeing eat image %d\n", i);
            mlx_destroy_image(mlx, player->eat[i].img);
            player->eat[i].img = NULL;
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
        if (game->heart.img) {
            printf("Freeing heart image\n");
            mlx_destroy_image(game->mlx, game->heart.img);
            game->heart.img = NULL;
        }
        if (game->heart_half.img) {
            printf("Freeing heart_half image\n");
            mlx_destroy_image(game->mlx, game->heart_half.img);
            game->heart_half.img = NULL;
        }
        if (game->bg.img) {
            printf("Freeing bg image\n");
            mlx_destroy_image(game->mlx, game->bg.img);
            game->bg.img = NULL;
        }
        if (game->wall.img) {
            printf("Freeing wall image\n");
            mlx_destroy_image(game->mlx, game->wall.img);
            game->wall.img = NULL;
        }
        if (game->coll.img) {
            printf("Freeing coll image\n");
            mlx_destroy_image(game->mlx, game->coll.img);
            game->coll.img = NULL;
        }
        if (game->trap.img) {
            printf("Freeing trap image\n");
            mlx_destroy_image(game->mlx, game->trap.img);
            game->trap.img = NULL;
        }
        if (game->door_c.img) {
            printf("Freeing door_c image\n");
            mlx_destroy_image(game->mlx, game->door_c.img);
            game->door_c.img = NULL;
        }
        if (game->door_o.img) {
            printf("Freeing door_o image\n");
            mlx_destroy_image(game->mlx, game->door_o.img);
            game->door_o.img = NULL;
        }
    }
}

void free_game(t_game *game) {
    if (game) {
        printf("Freeing player\n");
        free_player(&game->player, game->mlx);
        printf("Freeing map\n");
        free_map(game->map, game->map_height);
        printf("Freeing images\n");
        free_images(game);
        if (game->win) {
            printf("Destroying window\n");
            mlx_destroy_window(game->mlx, game->win);
            game->win = NULL;
        }
        if (game->mlx) {
            printf("Freeing mlx\n");
            free(game->mlx);
            game->mlx = NULL;
        }
    }
}

//valgrind --leak-check=full --show-leak-kinds=all ./so_long example1.ber
