/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:09:06 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/20 13:37:31 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		if (ft_printchar(str[i]) < 0)
			return (-1);
		i++;
	}
	return (i);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*d;

	d = dst;
	while ((*src))
	{
		*d = *src;
		d++;
		src++;
	}
	*d = '\0';
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	num = n;
	len = num_len(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
