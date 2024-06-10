/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/10 10:46:09 by bbogdano         ###   ########.fr       */
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
	void	*player_img;
	void	*collectible_img;
	void	*wall_img;
	void	*exit_img;
	void	*background_img;
	char	**map;
	int		img_width;
	int		img_height;
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
