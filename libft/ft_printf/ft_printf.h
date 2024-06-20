/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:04:56 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/20 14:44:01 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

//ft_printf.c
int		ft_printf(const char *str, ...);

//ft_sprintf.c
int		ft_vsprintf(char *buffer, const char *format, va_list args);
int		ft_sprintf(char *str, const char *format, ...);

//ft_snprintf.c
int		ft_snprintf(char *str, size_t size, const char *format, ...);

//text_helpers.c
int		ft_printchar(int c);
int		ft_printstr(char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_itoa(int n);

//nbr_helpers.c
int		ft_printnbr(int n);
int		ft_printunsigned(unsigned int n);
int		num_len(int num);

//hex_helpers.c
int		ft_printptr(void *ptr);
int		ft_printhex(unsigned long nbr, const char *hexbase);

#endif