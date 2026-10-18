/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayoshid <kayoshid@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:27:22 by kayoshid          #+#    #+#             */
/*   Updated: 2026/10/17 13:28:54 by kayoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_printf(const char *format, ...);
int	ft_print_char(char character);
int	ft_print_string(const char *string);
int	ft_print_number(unsigned long number, unsigned int base, int uppercase);
int	ft_print_signed(int number);
int	ft_print_pointer(void *pointer);

#endif
