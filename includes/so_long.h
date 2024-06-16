/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/16 16:56:01 by bbogdano         ###   ########.fr       */
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
# include <sys/time.h>

typedef struct s_img
{
	void	*img;
}	t_img;

typedef struct s_player
{
	t_img	idle[12];
	t_img	run[72];
	t_img	dmg[8];
	t_img	die[12];
	t_img	eat[10];
	int		future_x;
	int		future_y;
	int		x;
	int		y;
	int		hp;
}	t_player;

typedef struct s_flood_fill_state
{
	int	coll_found;
	int	exit_found;
}	t_flood_fill_state;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		bg;
	t_img		wall;
	t_img		coll;
	t_img		trap;
	t_img		door_c;
	t_img		door_o;
	t_player	player;
	char		**map;
	size_t		map_width;
	size_t		map_height;
	size_t		tile_size;
	int			collected;
	int			total_coll;
	int			anim_frame;
	int			timer;
	int			last_key;
	int			is_running;
	char		run_direction;
	struct		timeval last_update_time;
}	t_game;

// error.c
void	handle_error(char *message);

// load_images.c
int		load_images(t_game *game);

// scale_image.c
void	scale_image(void *mlx, t_img *img);

// read_map.c
int		get_map_dimensions(char *file, t_game *game);
int		read_map(char *file, t_game *game);

// render_map.c
void	put_image(t_game *game, t_img *img, int x, int y);
void	render_map(t_game *game);


// validate_elements.c
int		validate_elements(t_game *game);

// validate_flood_fill.c
void	validate_accessibility(t_game *game, int total_coll);

// validate_map.c
void	validate_map(t_game *game);

// gameplay.c
int  key_handler(int keycode, t_game *game);
int  game_loop(t_game *game);
void update_player_position(int keycode, t_game *game);
void move_player(t_game *game, int new_x, int new_y);

// handle_actions.c
void handle_trap(t_game *game);
void handle_collectible(t_game *game, int new_x, int new_y);
void handle_exit(t_game *game);


#endif