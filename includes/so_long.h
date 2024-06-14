/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 17:14:01 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>

typedef struct s_img {
    void    *img;
}   t_img;

typedef struct s_player {
    t_img   idle[12];
    t_img   run[72];
    t_img   dmg[8];
    t_img   die[12];
    t_img   eat[10];
}   t_player;

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_img   bg;
    t_img   wall;
    t_img   coll;
    t_img   trap;
    t_img   door_c;
    t_img   door_o;
    t_player player;
    char    **map;
    size_t  map_width;
    size_t  map_height;
    size_t  tile_size;
}   t_game;

//load_images.c
int	init_game(t_game *game);
void load_img(void *mlx, t_img *img, const char *path);
void    load_static_img(t_game *game);
void    load_player(t_game *game);
void load_anim(void *mlx, t_img *imgs, char *prefix, size_t count);

//main.c
void	draw_tile(t_game *game, t_img *img, int x, int y);
void	render_map(t_game *game, char **map, size_t rows, size_t cols);
int		handle_keypress(int keycode, t_game *game);
void	handle_error(char *message);

//read_map.c
char	**read_map(const char *filename, size_t *rows, size_t *cols);

#endif
