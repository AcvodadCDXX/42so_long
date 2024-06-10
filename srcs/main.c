/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:03:52 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/10 10:14:01 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

int main(int argc, char **argv)
{
    t_game game;
    size_t rows, cols;

    if (argc != 2)
        handle_error("Usage: ./so_long <map_file>");

    game.map = read_map(argv[1], &rows, &cols);
    validate_map(game.map, rows, cols);

    // Initialize MiniLibX and create a window
    game.mlx = mlx_init();
    if (!game.mlx)
        handle_error("Error: Failed to initialize MiniLibX");
    game.win = mlx_new_window(game.mlx, cols * TILE_SIZE, rows * TILE_SIZE, "So Long");
    if (!game.win)
        handle_error("Error: Failed to create window");

    // Render the map (placeholder, no actual rendering logic yet)
    // ...

    // Start the MiniLibX event loop
    mlx_loop(game.mlx);

    return 0;
}
