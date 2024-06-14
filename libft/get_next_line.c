/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:09:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/14 19:03:29 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

static char	*get_line(char **str)
{
	char	*line;
	char	*temp;
	size_t	len;

	len = 0;
	while ((*str)[len] && (*str)[len] != '\n')
		len++;
	if ((*str)[len] == '\n')
	{
		line = ft_substr(*str, 0, len);
		temp = ft_strdup(*str + len + 1);
		free(*str);
		*str = temp;
		if (!**str)
		{
			free(*str);
			*str = NULL;
		}
	}
	else
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	return (line);
}

static int	read_file(int fd, char **str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!*str)
			*str = ft_strdup("");
		temp = ft_strjoin_free(*str, buffer);
		if (!temp)
			return (-1);
		*str = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (bytes_read);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[FD_SETSIZE];
	int			bytes_read;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	bytes_read = read_file(fd, &str[fd]);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && (!str[fd] || !*str[fd]))
	{
		*line = ft_strdup("");
		return (0);
	}
	*line = get_line(&str[fd]);
	if (!*line)
		return (-1);
	return (1);
}
