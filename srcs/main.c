/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:53:23 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 17:09:51 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	draw_tile(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * 64, y * 64);
}

void	render_map(t_game *game, char **map, size_t rows, size_t cols)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			draw_tile(game, &game->bg, j, i);
			if (map[i][j] == '1')
				draw_tile(game, &game->wall, j, i);
			else if (map[i][j] == 'C')
				draw_tile(game, &game->coll, j, i);
			else if (map[i][j] == 'E')
				draw_tile(game, &game->door_c, j, i); // Default to closed door
			else if (map[i][j] == 'P')
				draw_tile(game, &game->player.idle[0], j, i); // Initial player frame
			j++;
		}
		i++;
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	(void)game;
	if (keycode == 65307) // ESC key
		exit(EXIT_SUCCESS);
	// Add more key handling here for movement
	return (0);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        handle_error("Usage: ./so_long <map_file>");
    (void)argv;
    init_game(&game);
    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);
    return (0);
}
