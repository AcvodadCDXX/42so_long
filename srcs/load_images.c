/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:53:44 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 17:18:20 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_img(void *mlx, t_img *img, const char *path)
{
    img->img = mlx_xpm_file_to_image(mlx, (char *)path, &(int){0}, &(int){0});
    if (!img->img)
    {
        printf("Error: Failed to load image at path: %s\n", path);
        handle_error("Failed to load image");
    }
}

void load_static_img(t_game *game)
{
    load_img(game->mlx, &game->bg, "assets/xpm/bg.xpm");
    load_img(game->mlx, &game->wall, "assets/xpm/wall.xpm");
    load_img(game->mlx, &game->coll, "assets/xpm/coll.xpm");
    load_img(game->mlx, &game->trap, "assets/xpm/trap.xpm");
    load_img(game->mlx, &game->door_c, "assets/xpm/doorC.xpm");
    load_img(game->mlx, &game->door_o, "assets/xpm/doorO.xpm");
}

void load_anim(void *mlx, t_img *img, char *prefix, size_t count)
{
    char path[256];
    size_t i = 0;

    while (i < count)
    {
        snprintf(path, sizeof(path), "assets/xpm/%s%zu.xpm", prefix, i + 1); // Use %zu for size_t
        printf("Loading image: %s\n", path);
        load_img(mlx, &img[i], path);
        i++;
    }
}

void load_player(t_game *game)
{
    load_anim(game->mlx, game->player.idle, "idleL", 6);
    load_anim(game->mlx, game->player.idle + 6, "idleR", 6);
    load_anim(game->mlx, game->player.run, "DsrcL", 6);
    load_anim(game->mlx, game->player.run + 6, "DsrcR", 6);
    load_anim(game->mlx, game->player.run + 12, "DdstL", 6);
    load_anim(game->mlx, game->player.run + 18, "DdstR", 6);
    load_anim(game->mlx, game->player.run + 24, "UsrcL", 6);
    load_anim(game->mlx, game->player.run + 30, "UsrcR", 6);
    load_anim(game->mlx, game->player.run + 36, "UdstL", 6);
    load_anim(game->mlx, game->player.run + 42, "UdstR", 6);
    load_anim(game->mlx, game->player.run + 48, "LsrcL", 6);
    load_anim(game->mlx, game->player.run + 54, "LdstL", 6);
    load_anim(game->mlx, game->player.run + 60, "RsrcR", 6);
    load_anim(game->mlx, game->player.run + 66, "RdstR", 6);
    load_anim(game->mlx, game->player.dmg, "dmgL", 4);
    load_anim(game->mlx, game->player.dmg + 4, "dmgR", 4);
    load_anim(game->mlx, game->player.die, "dieL", 6);
    load_anim(game->mlx, game->player.die + 6, "dieR", 6); 
    load_anim(game->mlx, game->player.eat, "eatL", 5);
    load_anim(game->mlx, game->player.eat + 5, "eatR", 5);
}

int	init_game(t_game *game)
{
	size_t	rows;
	size_t	cols;

	game->mlx = mlx_init();
	if (!game->mlx)
		handle_error("Error: MLX initialization failed");

	game->map = read_map("example1.ber", &rows, &cols);
	game->map_height = rows;
	game->map_width = cols;
	game->tile_size = 64;

	game->win = mlx_new_window(game->mlx, game->map_width * game->tile_size,
		game->map_height * game->tile_size, "so_long");
	if (!game->win)
		handle_error("Error: Window creation failed");

	load_static_img(game);
	load_player(game);
	return (0);
}