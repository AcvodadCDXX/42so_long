/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:53:23 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/21 15:22:05 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	initialize_mlx(t_game *game)
{
	int	screen_width;
	int	screen_height;
	int	window_width;
	int	window_height;

	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error("Failed to initialize MLX");
	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	game->tile_size = 64;
	window_width = game->map_width * game->tile_size;
	window_height = game->map_height * game->tile_size;
	if (window_width > screen_width)
		window_width = screen_width;
	if (window_height > screen_height)
		window_height = screen_height;
	game->win = mlx_new_window(game->mlx, \
	window_width, window_height, "so_long");
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
	game->player.state = IDLE;
	game->is_running = 0;
	find_player_position(game);
	gettimeofday(&game->last_update_time, NULL);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error("Usage: ./so_long <map_file>");
	initialize_game(&game, argv[1]);
	initialize_mlx(&game);
	validate_map(&game);
	if (!load_images(&game))
		handle_error("Failed to load images");
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, 17, 0, close_handler, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	draw_map(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
