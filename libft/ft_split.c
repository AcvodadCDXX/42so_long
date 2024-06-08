/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:23:43 by bbogdano          #+#    #+#             */
/*   Updated: 2023/06/27 12:34:17 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//in_substr = flag for word counting
static int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	in_substr;

	in_substr = 0;
	count = 0;
	while (*s != '\0')
	{
		if (in_substr == 1 && *s == c)
			in_substr = 0;
		if (in_substr == 0 && *s != c)
		{
			in_substr = 1;
			count++;
		}
		s++;
	}
	return (count);
}

//in this context i = index of last successfully allocated str
static void	ft_freeall(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

//len = s - start from process_word
static int	ft_allcopy(char **result, char const *start, size_t len)
{
	*result = (char *)malloc(sizeof(char) * (len + 1));
	if (*result == NULL)
		return (0);
	ft_strlcpy(*result, start, len + 1);
	return (1);
}

//using ptr to modify const = undefined behavior. Use w care
static char	*process_word(char const *s, char c, char **result, int i)
{
	char	*start;

	start = (char *)s;
	while (*s != c && *s != '\0')
		s++;
	if (!ft_allcopy(&result[i], start, s - start))
	{
		ft_freeall(result, i);
		return (NULL);
	}
	return ((char *)s);
}

//2d array, i=word count index for result array
//result = allocates memory for the array of pointers
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			s = process_word(s, c, result, i);
			if (!s)
				return (NULL);
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
