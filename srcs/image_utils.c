/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 00:16:53 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/19 13:46:11 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * 64, y * 64);
}

static void	scale_pixel(int *new_data, int *data, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			new_data[y * width + x] = data[(y / 4) * 16 + (x / 4)];
			x++;
		}
		y++;
	}
}

void	scale_image(void *mlx, t_img *img)
{
	void	*new_img;
	int		*data;
	int		*new_d;
	void	*old_img;

	old_img = img->img;
	new_img = mlx_new_image(mlx, 64, 64);
	if (!new_img)
		return ;
	data = (int *)mlx_get_data_addr(img->img, &(int){0}, &(int){0}, &(int){0});
	new_d = (int *)mlx_get_data_addr(new_img, &(int){0}, &(int){0}, &(int){0});
	scale_pixel(new_d, data, 64, 64);
	img->img = new_img;
	if (old_img)
	{
		mlx_destroy_image(mlx, old_img);
		old_img = NULL;
	}
}
