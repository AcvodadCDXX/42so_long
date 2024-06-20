/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:31:06 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/20 13:39:39 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	format_spec(char str, va_list args, char **buffer)
{
	int		count;
	char	*str_value;
	char	*int_value;

	count = 0;
	if (str == 'd' || str == 'i')
	{
		int_value = ft_itoa(va_arg(args, int));
		if (!int_value)
			return (-1);
		ft_strcpy(*buffer, int_value);
		count = ft_strlen(int_value);
		*buffer += count;
		free(int_value);
	}
	else if (str == 's')
	{
		str_value = va_arg(args, char *);
		ft_strcpy(*buffer, str_value);
		count = ft_strlen(str_value);
		*buffer += count;
	}
	return (count);
}

static int	process_char(const char *str, size_t *i,
						va_list args, char **buffer)
{
	int	count;

	count = 0;
	if (str[*i] == '%')
	{
		(*i)++;
		count = format_spec(str[*i], args, buffer);
	}
	else
	{
		**buffer = str[*i];
		(*buffer)++;
		count++;
	}
	(*i)++;
	return (count);
}

int	ft_vsprintf(char *buffer, const char *format, va_list args)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (format[i])
		count += process_char(format, &i, args, &buffer);
	*buffer = '\0';
	return (count);
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = ft_vsprintf(str, format, args);
	va_end(args);
	return (count);
}
