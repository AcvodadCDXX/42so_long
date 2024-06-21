/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:26 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/21 15:16:05 by bbogdano         ###   ########.fr       */
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
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	close_handler(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
