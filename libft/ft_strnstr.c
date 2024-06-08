/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:39:14 by bbogdano          #+#    #+#             */
/*   Updated: 2023/06/26 15:36:46 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//looks for small in big up to len chars, outer loop for traversing big,
//inner loop for traversing small. Ctrl+f
char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	bigi;
	size_t	smalli;

	if (*small == '\0')
		return ((char *)big);
	bigi = 0;
	while (big[bigi] != '\0' && bigi < len)
	{
		smalli = 0;
		while (big[bigi + smalli] == small[smalli] && (bigi + smalli) < len)
		{
			if (small[smalli + 1] == '\0')
				return ((char *)&big[bigi]);
			smalli++;
		}
		bigi++;
	}
	return (0);
}
