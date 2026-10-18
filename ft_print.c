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
	int	length;

	if (!string)
		string = "(null)";
	length = 0;
	while (string[length])
	{
		if (length == INT_MAX || ft_print_char(string[length]) < 0)
			return (-1);
		length++;
	}
	return (length);
}

int	ft_print_number(unsigned long number, unsigned int base, int uppercase)
{
	const char	*digits;
	int			length;

	digits = "0123456789abcdef";
	if (uppercase)
		digits = "0123456789ABCDEF";
	length = 0;
	if (number >= base)
		length = ft_print_number(number / base, base, uppercase);
	if (length < 0 || ft_print_char(digits[number % base]) < 0)
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
