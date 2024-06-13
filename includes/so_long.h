/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/12 14:18:33 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <string.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_pos
{
    int x;
    int y;
}   t_pos;

typedef struct s_spr {
    void    *img;
    void    *scaled_img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     w;
    int     h;
    int     scale;
} t_spr;

typedef struct s_game {
    void        *mlx;
    void        *win;
    t_spr       player;
    t_spr       collectible;
    t_spr       wall;
    t_spr       exit;
    t_spr       background;
    t_spr       buffer; // Add buffer here
    char        **map;
    size_t      map_w;
    size_t      map_h;
    int         img_w;
    int         img_h;
    t_pos       player_pos;
} t_game;


char    **read_map(const char *filename, size_t *rows, size_t *cols);
void    validate_map(char **map, size_t rows, size_t cols);
void    render_map(t_game *game);
void    handle_error(const char *message);
void validate_map_elements(char **map, size_t rows, size_t cols);
void flood_fill(char **map, int x, int y, int *collectibles, int *exit);
void validate_map_path(char **map, size_t rows, size_t cols);
void load_images(t_game *game);
int init_game(t_game *game, char *map_file);
void scale_image(void *mlx, t_spr *sprite, int scale_factor);


#endif
