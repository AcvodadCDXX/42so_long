/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:08:11 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/20 11:53:42 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_printstr("-2147483648"));
	if (n < 0)
	{
		i = ft_printchar('-');
		if (i == -1)
			return (-1);
		n = -n;
	}
	i += ft_printunsigned((unsigned int)n);
	return (i);
}

int	ft_printunsigned(unsigned int n)
{
	int		i;

	i = 0;
	if (n >= 10)
	{
		i = ft_printunsigned(n / 10);
		if (i == -1)
			return (-1);
	}
	i += ft_printchar((int)(n % 10 + '0'));
	return (i);
}

int	num_len(int num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}
