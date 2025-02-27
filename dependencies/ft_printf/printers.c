/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:06:12 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/24 16:48:44 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	print_char(char c)
{
	write(STDOUT_FILENO, &c, 1);
	return (1);
}

int	print_string(char *str)
{
	size_t	len;

	if (!str)
	{
		write(STDOUT_FILENO, "(nil)", 5);
		return (5);
	}
	len = ft_strlen(str);
	write(STDOUT_FILENO, str, len);
	return (len);
}

int	print_integer(long long number)
{
	int	len;

	len = 0;
	if (!number)
		return (print_char('0'));
	if (number < 0)
	{
		len += print_char('-');
		number *= -1;
	}
	if (number < 10)
		return (len += print_char(number + '0'));
	len += print_integer(number / 10);
	len += print_char(number % 10 + '0');
	return (len);
}
