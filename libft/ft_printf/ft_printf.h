/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:04:56 by bbogdano          #+#    #+#             */
/*   Updated: 2024/06/07 12:05:08 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);

int	ft_printchar(int c);
int	ft_printstr(char *str);

int	ft_printnbr(int n);
int	ft_printunsigned(unsigned int n);

int	ft_printptr(void *ptr);
int	ft_printhex(unsigned long nbr, const char *hexbase);

#endif