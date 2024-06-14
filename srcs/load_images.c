/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:53:44 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 16:11:53 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_img(void *mlx, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(mlx, path, NULL, NULL);
    if (!img->img) {
        ft_putstr_fd("Error loading img: ", 2);
        ft_putendl_fd(path, 2);
        exit(EXIT_FAILURE);
    }
}

void load_static_img(t_game *game)
{
    load_img(game->mlx, &game->bg, "assets/xpm/bg.xpm");
    load_img(game->mlx, &game->wall, "assets/xpm/wall.xpm");
    load_img(game->mlx, &game->door_c, "assets/xpm/doorC.xpm");
    load_img(game->mlx, &game->door_o, "assets/xpm/doorO.xpm");
    load_img(game->mlx, &game->coll, "assets/xpm/coll.xpm");
    load_img(game->mlx, &game->trap, "assets/xpm/trap.xpm");
}

void load_anim(void *mlx, t_img *img_array, char *base_path, int frames)
{
    int i;
    char path[50];
    char *frame_str;

    i = 0;
    while (i < frames) {
        ft_strlcpy(path, base_path, 50);
        frame_str = ft_itoa(i + 1);
        ft_strlcat(path, frame_str, 50);
        ft_strlcat(path, ".xpm", 50);
        free(frame_str);
        load_img(mlx, &img_array[i], path);
        i++;
    }
}

void load_player(t_game *game)
{
    load_anim(game->mlx, game->idle, "assets/xpm/idleL", 6);
    load_anim(game->mlx, game->idle + 6, "assets/xpm/idleR", 6);
    load_anim(game->mlx, game->run, "assets/xpm/DsrcL", 6);
    load_anim(game->mlx, game->run + 6, "assets/xpm/DsrcR", 6);
    load_anim(game->mlx, game->run + 12, "assets/xpm/DdstL", 6);
    load_anim(game->mlx, game->run + 18, "assets/xpm/DdstR", 6);
    load_anim(game->mlx, game->run + 24, "assets/xpm/UsrcL", 6);
    load_anim(game->mlx, game->run + 30, "assets/xpm/UsrcR", 6);
    load_anim(game->mlx, game->run + 36, "assets/xpm/UdstL", 6);
    load_anim(game->mlx, game->run + 42, "assets/xpm/UdstR", 6);
    load_anim(game->mlx, game->run + 48, "assets/xpm/Lsrc", 6);
    load_anim(game->mlx, game->run + 54, "assets/xpm/Ldst", 6);
    load_anim(game->mlx, game->run + 60, "assets/xpm/Rsrc", 6);
    load_anim(game->mlx, game->run + 66, "assets/xpm/Rdst", 6);
    load_anim(game->mlx, game->damage, "assets/xpm/dmgL", 4);
    load_anim(game->mlx, game->damage + 4, "assets/xpm/dmgR", 4);
    load_anim(game->mlx, game->die, "assets/xpm/dieL", 6);
    load_anim(game->mlx, game->die + 6, "assets/xpm/dieR", 6);
    load_anim(game->mlx, game->eat, "assets/xpm/eatL", 5);
    load_anim(game->mlx, game->eat + 5, "assets/xpm/eatR", 5);
}

void init_game(t_game *game) {
    game->mlx = mlx_init();
    if (!game->mlx)
        handle_error("MLX init failed");
    game->win = mlx_new_window(game->mlx, 800, 600, "so_long");
    if (!game->win)
        handle_error("Window creation failed");
    load_static_img(game);
    load_player(game);
}