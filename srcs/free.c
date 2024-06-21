/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:55:32 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/21 15:23:01 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_image_array(t_img *images, int count, void *mlx)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (images[i].img)
			mlx_destroy_image(mlx, images[i].img);
		i++;
	}
}

void	free_player(t_player *player, void *mlx)
{
	free_image_array(player->idle, 12, mlx);
	free_image_array(player->run, 72, mlx);
	free_image_array(player->dmg, 8, mlx);
	free_image_array(player->die, 12, mlx);
	free_image_array(player->eat, 10, mlx);
}

void	free_map(char **map, size_t height)
{
	size_t	i;

	if (map)
	{
		i = 0;
		while (i < height)
		{
			if (map[i])
				free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_images(t_game *game)
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

void	free_game(t_game *game)
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

//valgrind --leak-check=full --show-leak-kinds=all ./so_long map1.ber