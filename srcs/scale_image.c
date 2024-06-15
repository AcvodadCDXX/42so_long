/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:18:37 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/15 13:40:48 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	int		width;
	int		height;

	width = 64;
	height = 64;
	new_img = mlx_new_image(mlx, width, height);
	data = (int *)mlx_get_data_addr(img->img, &(int){0}, &(int){0}, &(int){0});
	new_d = (int *)mlx_get_data_addr(new_img, &(int){0}, &(int){0}, &(int){0});
	scale_pixel(new_d, data, width, height);
	img->img = new_img;
}
