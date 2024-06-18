/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:07:20 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/18 13:48:28 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_spec(char str, va_list *args)
{
	int	count;

	count = 0;
	if (str == '%')
		count += ft_printchar('%');
	else if (str == 'c')
		count += ft_printchar(va_arg(*args, int));
	else if (str == 's')
		count += ft_printstr(va_arg(*args, char *));
	else if (str == 'i' || str == 'd')
		count += ft_printnbr(va_arg(*args, int));
	else if (str == 'u')
		count += ft_printunsigned(va_arg(*args, unsigned int));
	else if (str == 'x')
		count += ft_printhex(va_arg(*args, unsigned int), "0123456789abcdef");
	else if (str == 'X')
		count += ft_printhex(va_arg(*args, unsigned int), "0123456789ABCDEF");
	else if (str == 'p')
		count += ft_printptr(va_arg(*args, void *));
	return (count);
}

static int	process_char(const char *str, size_t *i, va_list *args)
{
	int	count;

	count = 0;
	if (str[*i] == '%')
	{
		(*i)++;
		count = format_spec(str[*i], args);
	}
	else
		count = ft_printchar(str[*i]);
	(*i)++;
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += process_char(str, &i, &args);
		}
		else
		{
			count += ft_printchar(str[i]);
			i++;
		}
		if (count == -1)
			break ;
	}
	va_end(args);
	return (count);
}
