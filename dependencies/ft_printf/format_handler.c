/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:21 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/24 16:45:21 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	handle_format(const char *buffer, va_list args, int idx)
{
	int	total_length;
	int	count;

	if (!buffer)
		return (0);
	count = idx + 1;
	total_length = 0;
	if (buffer[count] == 'c')
		total_length += print_char(va_arg(args, int));
	else if (buffer[count] == 'd')
		total_length += print_integer(va_arg(args, int));
	else if (buffer[count] == 's')
		total_length += print_string(va_arg(args, char *));
	else
		total_length += print_char(buffer[count]);
	return (total_length);
}
