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

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *player_img;
    void    *collectible_img;
    void    *wall_img;
    void    *exit_img;
    void    *background_img;
    char    **map;
    size_t  map_width;
    size_t  map_height;
    int     img_width;
    int     img_height;
}   t_game;

char    **read_map(const char *filename, size_t *rows, size_t *cols);
void    validate_map(char **map, size_t rows, size_t cols);
void    render_map(t_game *game);
void    handle_error(const char *message);
void validate_map_elements(char **map, size_t rows, size_t cols);
void flood_fill(char **map, int x, int y, int *collectibles, int *exit);
void validate_map_path(char **map, size_t rows, size_t cols);

#endif
