/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayoshid <kayoshid@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:27:22 by kayoshid          #+#    #+#             */
/*   Updated: 2026/10/17 13:28:54 by kayoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <limits.h>

static int	ft_conversion(char specifier, va_list *args)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(*args, int)));
	if (specifier == 's')
		return (ft_print_string(va_arg(*args, char *)));
	if (specifier == 'p')
		return (ft_print_pointer(va_arg(*args, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_print_signed(va_arg(*args, int)));
	if (specifier == 'u')
		return (ft_print_number(va_arg(*args, unsigned int), 10, 0));
	if (specifier == 'x' || specifier == 'X')
		return (ft_print_number(va_arg(*args, unsigned int), 16,
				specifier == 'X'));
	if (specifier == '%')
		return (ft_print_char('%'));
	return (-1);
}

static int	ft_format(const char *format, va_list *args)
{
	int	count;
	int	written;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			written = ft_conversion(*format, args);
		}
		else
			written = ft_print_char(*format);
		if (written < 0 || count > INT_MAX - written)
			return (-1);
		count += written;
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = ft_format(format, &args);
	va_end(args);
	return (count);
}
