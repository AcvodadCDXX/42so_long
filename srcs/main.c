/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:53:23 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/16 16:56:58 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_arguments(int argc)
{
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <map_file>", 2);
		exit(EXIT_FAILURE);
	}
}

static void	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error("Failed to initialize mlx");
	game->win = mlx_new_window(game->mlx, 1920, 1080, "so_long");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		handle_error("Failed to create window");
	}
}

void initialize_game(t_game *game, char *map_file)
{
    if (!read_map(map_file, game))
        handle_error("Failed to read map");

    validate_elements(game);

    game->anim_frame = 0;
    game->timer = 0;
    game->last_key = 97;  // Default to facing left ('A')
    game->player.hp = 2;  // Initialize player health

    // Scan the map for the player's initial position
    for (size_t y = 0; y < game->map_height; y++)
    {
        for (size_t x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == 'P')
            {
                game->player.x = x;
                game->player.y = y;
                break;
            }
        }
    }

    gettimeofday(&game->last_update_time, NULL);  // Initialize last update time

    if (!load_images(game))
        handle_error("Failed to load images");
}


int close_handler(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
    return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_arguments(argc);
	initialize_mlx(&game);
	initialize_game(&game, argv[1]);
	validate_map(&game);
	mlx_key_hook(game.win, key_handler, &game);
    mlx_hook(game.win, 17, 0, close_handler, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
	render_map(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
