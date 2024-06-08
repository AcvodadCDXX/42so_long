/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:03:52 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/08 01:34:53 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
		handle_error("Usage: ./so_long <map_file.ber>");
	check_file(argv[1]);
}

int	main(int argc, char **argv)
{
	t_game	game;

	validate_arguments(argc, argv);
	if (!init_game(&game, argv[1]))
		handle_error("Error: Failed to initialize game.");
	//gameloop
	cleanup_game(&game);
	return (0);
}
