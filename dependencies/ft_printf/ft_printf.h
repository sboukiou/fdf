/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:47:51 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/24 16:48:13 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include "../libft/libft.h"

/*Printers defintions*/
int	print_char(char c);
int	print_integer(long long number);
int	print_string(char *str);
int	ft_printf(const char *buffer, ...);
int	handle_format(const char *buffer, va_list args, int idx);
#endif
