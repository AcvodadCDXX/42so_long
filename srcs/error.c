/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:26 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 14:54:42 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	handle_victory(t_game *game)
{
	ft_printf("You win!\n");
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}
