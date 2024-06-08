/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:08:48 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/07 12:08:53 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printhex(unsigned long nbr, const char *hexbase)
{
	int	i;

	i = 0;
	if (nbr >= 16)
	{
		i += ft_printhex(nbr / 16, hexbase);
		if (i == -1)
			return (-1);
	}
	i += ft_printchar(hexbase[nbr % 16]);
	return (i);
}

int	ft_printptr(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		count = ft_printstr("0x0");
	else
	{
		count = ft_printstr("0x");
		if (count == -1)
			return (-1);
		count += ft_printhex((unsigned long)ptr, "0123456789abcdef");
	}
	return (count);
}
