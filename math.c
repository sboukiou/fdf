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
