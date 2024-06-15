/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 15:48:11 by bbogdano         ###   ########.fr       */
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

typedef struct s_flood_fill_state {
	int	collectibles_found;
	int	exit_found;
}	t_flood_fill_state;

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
    int     collected;           // Number of collected items
    int     total_collectibles;  // Total number of collectibles in the map
    int     anim_frame;          // Current animation frame
    int     timer;               // Timer for managing animations
}   t_game;
//error.c
void	handle_error(char *message);

//load_images.c
void	load_img(void *mlx, t_img *img, const char *path);
void load_static_img(t_game *game);
void	load_anim(void *mlx, t_img *img, char *prefix, size_t count);
void	load_player(t_game *game);
int	load_images(t_game *game);

//scale_image.c
void	scale_image(void *mlx, t_img *img);

//read_map.c
int	get_map_dimensions(char *file, t_game *game);
int	read_map(char *file, t_game *game);

//render_map.c
void	put_image(t_game *game, t_img *img, int x, int y);
void	render_map(t_game *game);

//validate_elements.c
int	validate_elements(t_game *game);

//validate_flood_fill.c
void	validate_accessibility(t_game *game, int total_coll);

//validate_map.c
void	validate_map(t_game *game);


#endif
