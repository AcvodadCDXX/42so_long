/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:53:44 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/19 11:10:45 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_img(void *mlx, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(mlx, path, &(int){0}, &(int){0});
    if (!img->img)
    {
        fprintf(stderr, "Failed to load image: %s\n", path);
        exit(EXIT_FAILURE);
    }
}

static void	load_static_img(t_game *game)
{
	load_img(game->mlx, &game->heart, "assets/xpm/heart.xpm");
	scale_image(game->mlx, &game->heart);
	load_img(game->mlx, &game->heart_half, "assets/xpm/heart_half.xpm");
	scale_image(game->mlx, &game->heart_half);
	load_img(game->mlx, &game->bg, "assets/xpm/bg.xpm");
	scale_image(game->mlx, &game->bg);
	load_img(game->mlx, &game->wall, "assets/xpm/wall.xpm");
	scale_image(game->mlx, &game->wall);
	load_img(game->mlx, &game->coll, "assets/xpm/coll.xpm");
	scale_image(game->mlx, &game->coll);
	load_img(game->mlx, &game->trap, "assets/xpm/trap.xpm");
	scale_image(game->mlx, &game->trap);
	load_img(game->mlx, &game->door_c, "assets/xpm/doorC.xpm");
	scale_image(game->mlx, &game->door_c);
	load_img(game->mlx, &game->door_o, "assets/xpm/doorO.xpm");
	scale_image(game->mlx, &game->door_o);
	load_img(game->mlx, &game->trap, "assets/xpm/trap.xpm");
	scale_image(game->mlx, &game->trap);
}

static void	load_anim(void *mlx, t_img *img, char *prefix, size_t count)
{
	char	path[256];
	size_t	i;

	i = 0;
	while (i < count)
	{
		snprintf(path, sizeof(path), "assets/xpm/%s%zu.xpm", prefix, i + 1);
		load_img(mlx, &img[i], path);
		scale_image(mlx, &img[i]);
		i++;
	}
}

static void	load_player(t_game *game)
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

int load_images(t_game *game) 
{
    load_static_img(game);
    load_player(game);
    return (1);
}