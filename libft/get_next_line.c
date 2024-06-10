/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:09:31 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/10 12:42:56 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function to extract a line from the buffer
static char *extract_line(char **buffer)
{
    char *line;
    char *newline_pos;
    char *temp;
    size_t len;

    if (!*buffer)
        return (NULL);
    
    newline_pos = ft_strchr(*buffer, '\n');
    if (newline_pos)
    {
        len = newline_pos - *buffer;
        line = ft_substr(*buffer, 0, len); // Adjusted to exclude '\n'
        temp = ft_strdup(*buffer + len + 1);
        free(*buffer);
        *buffer = temp;
        if (**buffer == '\0')
        {
            free(*buffer);
            *buffer = NULL;
        }
    }
    else
    {
        line = ft_strdup(*buffer);
        free(*buffer);
        *buffer = NULL;
    }
    return (line);
}

// Function to append read string to buffer
static int append_to_buffer(char **buffer, char *read_str, ssize_t read_len)
{
    char *temp;

    read_str[read_len] = '\0';
    if (*buffer)
    {
        temp = ft_strjoin(*buffer, read_str);
        free(*buffer);
        *buffer = temp;
    }
    else
    {
        *buffer = ft_strdup(read_str);
    }
    if (!*buffer)
        return (-1);
    return (1);
}

// Main function to get the next line from a file descriptor
int get_next_line(int fd, char **line)
{
    static char *buffer[1024];
    char read_str[BUFFER_SIZE + 1];
    ssize_t read_len;

    if (fd < 0 || fd >= 1024 || !line || BUFFER_SIZE <= 0)
        return (-1);

    while (!ft_strchr(buffer[fd], '\n'))
    {
        read_len = read(fd, read_str, BUFFER_SIZE);
        if (read_len < 0 || (read_len == 0 && !buffer[fd]))
            return (-1);
        if (read_len == 0)
            break ;
        if (append_to_buffer(&buffer[fd], read_str, read_len) < 0)
            return (-1);
    }
    *line = extract_line(&buffer[fd]);
    if (!*line)
        return (-1);
    if (buffer[fd] == NULL)
        return (0);
    return (1);
}
