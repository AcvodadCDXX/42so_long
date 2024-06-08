/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:29:14 by bbogdano          #+#    #+#             */
/*   Updated: 2023/06/26 00:44:27 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//function is used to copy n bytes from memory area src to memory area dst. 
//It returns the original value of dst.
void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	const char	*s;
	char		*d;
	void		*orig_dst;

	if (!dst && !src)
		return (0);
	s = (const char *)src;
	d = (char *)dst;
	orig_dst = dst;
	while (len--)
		*d++ = *s++;
	return (orig_dst);
}
