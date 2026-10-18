/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayoshid <kayoshid@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:27:22 by kayoshid          #+#    #+#             */
/*   Updated: 2026/10/17 13:28:54 by kayoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <unistd.h>
#include <limits.h>

int	ft_print_char(char character)
{
	if (write(1, &character, 1) != 1)
		return (-1);
	return (1);
}

int	ft_print_string(const char *string)
{
	size_t	length;
	ssize_t	written;
	int		count;

	if (!string)
		string = "(null)";
	length = ft_strlen(string);
	if (length > INT_MAX)
		return (-1);
	count = (int)length;
	while (length > 0)
	{
		written = write(1, string, length);
		if (written <= 0)
			return (-1);
		string += written;
		length -= written;
	}
	return (count);
}

int	ft_print_number(unsigned long number, unsigned int base, int uppercase)
{
	const char	*digits;
	char		digit;
	int			length;

	digits = "0123456789abcdef";
	length = 0;
	if (number >= base)
		length = ft_print_number(number / base, base, uppercase);
	digit = digits[number % base];
	if (uppercase)
		digit = ft_toupper(digit);
	if (length < 0 || ft_print_char(digit) < 0)
		return (-1);
	return (length + 1);
}

int	ft_print_signed(int number)
{
	unsigned int	magnitude;
	int				length;

	magnitude = number;
	if (number < 0)
	{
		if (ft_print_char('-') < 0)
			return (-1);
		magnitude = 0 - magnitude;
	}
	length = ft_print_number(magnitude, 10, 0);
	if (length < 0)
		return (-1);
	return (length + (number < 0));
}

int	ft_print_pointer(void *pointer)
{
	int	length;

	if (!pointer)
		return (ft_print_string("(nil)"));
	if (ft_print_string("0x") < 0)
		return (-1);
	length = ft_print_number((unsigned long)pointer, 16, 0);
	if (length < 0)
		return (-1);
	return (length + 2);
}
