/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:03:24 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 23:41:48 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

/**
	* distance - Calculates distance between two circles
	* Return: float point of distance (positive value always)
	*/
static int	ft_ishex_lower(char c)
{
	char	*hex;
	int		idx;

	hex = "0123456789abcdef";
	idx = 0;
	while (hex[idx])
	{
		if (c == hex[idx])
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

static int	ft_ishex_upper(char c)
{
	char	*hex;
	int		idx;

	hex = "0123456789ABCDEF";
	idx = 0;
	while (hex[idx])
	{
		if (c == hex[idx])
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

static int	index_of(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	handle_hex_lower(char *str)
{
	int		idx;
	int		color;
	char	*hex;

	idx = 2;
	hex = "0123456789abcdef";
	color = 0;
	while (str[idx] && ft_ishex_lower(str[idx]))
	{
		color *= 16;
		color += index_of(str[idx], hex);
		idx++;
	}
	return (color);
}

int	handle_hex_upper(char *str)
{
	int		idx;
	int		color;
	char	*hex;

	idx = 2;
	hex = "0123456789ABCDEF";
	color = 0;
	while (str[idx] && ft_ishex_upper(str[idx]))
	{
		color *= 16;
		color += index_of(str[idx], hex);
		idx++;
	}
	return (color);
}
