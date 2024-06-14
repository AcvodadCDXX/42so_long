/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:53:44 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 17:03:12 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_img(void *mlx, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(mlx, path, &(int){0}, &(int){0});
    if (!img->img)
    {
        ft_printf("Error: Failed to load image at path: %s\n", path);
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

void load_anim(void *mlx, t_img *imgs, char *prefix, size_t count)
{
    char path[128];
    size_t i;

    i = 0;
    while (i < count)
    {
        ft_printf(path, "assets/xpm/%s%lu.xpm", prefix, i + 1);
        load_img(mlx, &imgs[i], path);
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
    load_anim(game->mlx, game->player.run + 48, "Lsrc", 6);
    load_anim(game->mlx, game->player.run + 54, "Ldst", 6);
    load_anim(game->mlx, game->player.run + 60, "Rsrc", 6);
    load_anim(game->mlx, game->player.run + 66, "Rdst", 6);
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