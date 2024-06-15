/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:53:23 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 14:17:17 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_arguments(int argc)
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

static void	initialize_game(t_game *game, char *file)
{
	if (!load_images(game))
		handle_error("Failed to load images");
	if (!read_map(file, game))
		handle_error("Failed to read map");
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_arguments(argc);
	initialize_mlx(&game);
	initialize_game(&game, argv[1]);
	validate_map(&game);
	render_map(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
