/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:44:46 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/10 11:27:06 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t len_s1 = ft_strlen(s1);
    size_t len_s2 = ft_strlen(s2);
    char *new_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
    if (!new_str)
        return (NULL);
    ft_memcpy(new_str, s1, len_s1);
    ft_memcpy(new_str + len_s1, s2, len_s2 + 1);
    return (new_str);
}