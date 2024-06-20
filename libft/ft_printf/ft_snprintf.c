/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:44:48 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/20 14:44:18 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	size_t	count;
	char	*temp;

	temp = (char *)malloc(size * sizeof(char));
	if (!temp)
		return (-1);
	va_start(args, format);
	count = ft_vsprintf(temp, format, args);
	va_end(args);
	if (count >= size)
		count = size - 1;
	ft_strncpy(str, temp, count);
	str[count] = '\0';
	free(temp);
	return (count);
}
