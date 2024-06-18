/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 00:16:53 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 17:33:02 by bbogdano         ###   ########.fr       */
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

void scale_image(void *mlx, t_img *img) {
    void *new_img;
    int *data;
    int *new_d;
    int width = 64;
    int height = 64;
    void *old_img = img->img; // Save the original image

    new_img = mlx_new_image(mlx, width, height);
    if (!new_img) {
        // Handle error if new image creation fails
        return;
    }
    data = (int *)mlx_get_data_addr(img->img, &(int){0}, &(int){0}, &(int){0});
    new_d = (int *)mlx_get_data_addr(new_img, &(int){0}, &(int){0}, &(int){0});
    scale_pixel(new_d, data, width, height);
    img->img = new_img; // Update img to new image

    if (old_img) {
        mlx_destroy_image(mlx, old_img); // Destroy the original image
        old_img = NULL; // Nullify the pointer
    }
}
