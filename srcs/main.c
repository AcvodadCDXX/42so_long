/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:53:23 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 14:24:14 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error("Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, 1920, 1080, "so_long");
	if (!game->win)
		handle_error("Failed to create window");
}

static void	find_player_position(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	initialize_game(t_game *game, char *map_file)
{
	if (!read_map(map_file, game))
		handle_error("Failed to read map");
	validate_elements(game);
	game->anim_frame = 0;
	game->timer = 0;
	game->last_key = 97;
	game->player.hp = 2;
	game->player.move_count = 0;
	find_player_position(game);
	gettimeofday(&game->last_update_time, NULL);
	if (!load_images(game))
		handle_error("Failed to load images");
}

int	close_handler(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error("Usage: ./so_long <map_file>");
	initialize_mlx(&game);
	initialize_game(&game, argv[1]);
	validate_map(&game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, 17, 0, close_handler, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	draw_map(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
