/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/08 02:43:15 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_elements
{
	int start_count;
	int exit_count;
	int collect_count;
}	t_elements;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	// other game-related members
}	t_game;

int		init_game(t_game *game, char *map_file);
void	cleanup_game(t_game *game);
void	check_file(const char *filename);
void	validate_map(char **map, size_t rows, size_t cols);
void	flood_fill(char **tab, t_point size, t_point begin);
char	**read_map(const char *filename, size_t *rows, size_t *cols);
void	validate_map_elements(char **map, size_t rows, size_t cols);
void	validate_walls(char **map, size_t rows, size_t cols);
void	handle_error(char *message);

#endif
