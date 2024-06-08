/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:18:28 by bbogdano          #+#    #+#             */
/*   Updated: 2023/06/27 11:16:31 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//creates a new substr, returns it, unlike strnstr, which just returns a ptr
//s= big, start = start index, len = max size. If start>=s size, return \0
//if len < rest of str length use len, otherwise rest of str_len
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	str_len;
	char	*substring;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
	{
		substring = (char *)malloc(sizeof(char));
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (len < str_len - start)
		sub_len = len;
	else
		sub_len = str_len - start;
	substring = (char *)malloc((sub_len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, sub_len + 1);
	return (substring);
}
