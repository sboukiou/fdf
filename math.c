/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:03:24 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/27 20:25:10 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

/**
	* distance - Calculates distance between two circles
	* Return: float point of distance (positive value always)
	*/
int	distance(int x1, int y1, int x2, int y2)
{
	return (pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/**
	* ft_min - Returns min value of two ints
	*/
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
	* ft_min - Returns min value of two ints
	*/
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_ishex_lower(char c)
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
	int	idx;
	int	color;
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
	int	idx;
	int	color;
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

float	triangle_area(t_point a, t_point b, t_point extra)
{
	int	factor_1;
	int	factor_2;
	int	factor_3;

	factor_1 = (b.y - extra.y) * a.x;
	factor_2 = (extra.y - a.y) * b.x;
	factor_3 = (a.y - b.y) * extra.x;
	return (0.5 * (factor_1 + factor_2 + factor_3));
}
