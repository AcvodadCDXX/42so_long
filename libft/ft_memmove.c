/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 08:14:40 by bbogdano          #+#    #+#             */
/*   Updated: 2023/06/26 00:53:53 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//if null, return. Cast to char ptr since 1 byte size
//if d < s checks for memory address, if d lower copy from front
// if d higher, copy from back, return dst
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*lastd;
	const char	*lasts;

	if (!dst && !src)
		return (0);
	d = (char *) dst;
	s = (const char *) src;
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		lasts = (char *)(s + (len - 1));
		lastd = (char *)(d + (len - 1));
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
