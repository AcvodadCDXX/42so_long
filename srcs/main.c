/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:53:23 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 18:52:27 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <map_file>", 2);
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		handle_error("Failed to initialize mlx");
	game.win = mlx_new_window(game.mlx, 1920, 1080, "so_long");
	if (!game.win)
	{
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		handle_error("Failed to create window");
	}
	if (!load_images(&game))
		handle_error("Failed to load images");
	if (!read_map(argv[1], &game))
		handle_error("Failed to read map");
	render_map(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
