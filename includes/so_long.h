/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:50:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 16:57:38 by bbogdano         ###   ########.fr       */
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

typedef enum e_state
{
	IDLE,
	RUN,
	EAT,
	DMG,
	DIE
}	t_state;

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
	int		move_count;
	t_state	state;
}	t_player;

typedef struct s_flood_fill_state
{
	int	coll_found;
	int	exit_found;
}	t_flood_fill_state;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			heart;
	t_img			heart_half;
	t_img			bg;
	t_img			wall;
	t_img			coll;
	t_img			trap;
	t_img			door_c;
	t_img			door_o;
	t_player		player;
	char			**map;
	size_t			map_width;
	size_t			map_height;
	size_t			tile_size;
	int				collected;
	int				total_coll;
	int				anim_frame;
	int				timer;
	int				last_key;
	int				is_running;
	char			run_direction;
	struct timeval	last_update_time;
}	t_game;

// error.c
void	handle_error(char *message);
void	handle_victory(t_game *game);
void free_map(char **map, size_t height);

//free.c
void free_player(t_player *player, void *mlx);
void free_game(t_game *game);
void free_map(char **map, size_t height);
void free_images(t_game *game);

//main.c
int	close_handler(t_game *game);

// load_images.c
int		load_images(t_game *game);

// read_map.c
int		get_map_dimensions(char *file, t_game *game);
int		read_map(char *file, t_game *game);

// draw_map.c
void	draw_background(t_game *game);
void	draw_player_idle(t_game *game);
void	draw_map(t_game *game);

// image_utils.c
void	put_image(t_game *game, t_img *img, int x, int y);
void	scale_image(void *mlx, t_img *img);

// draw_player.c
void	draw_player_idle(t_game *game);
void	draw_player_run(t_game *game);
void	draw_player_eat(t_game *game);
void	draw_player_damage(t_game *game);
void	draw_player_death(t_game *game);

// validate_elements.c
int		validate_elements(t_game *game);

// validate_flood_fill.c
void	validate_accessibility(t_game *game, int total_coll);

// validate_map.c
void	validate_map(t_game *game);

// gameplay.c
int		key_handler(int keycode, t_game *game);
int		game_loop(t_game *game);
void	update_player_position(int keycode, t_game *game);

// player_movement.c
void	handle_movement(int keycode, t_game *game);
int		is_valid_move(t_game *game);
void	set_player_state(t_game *game);

//draw_player_run_utils.c
void	draw_run_left(t_game *game, int frame_offset);
void	draw_run_right(t_game *game, int frame_offset);
void	draw_run_up(t_game *game, int frame_offset);
void	draw_run_down(t_game *game, int frame_offset);
void	handle_post_run_animation(t_game *game);

//draw_hud.c
void	draw_hud(t_game *game);

#endif
