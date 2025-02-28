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
float	distance(t_pt a, t_pt b)
{
	return (pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/**
	* rectangle_are - Calculates Area of a rectangle
	* Return: float point of are (positive value always)
	*/
float	triangle_area(t_pt a, t_pt b, t_pt c)
{
	float factor_a;
	float factor_b;
	float factor_c;

	factor_a = a.x * (b.y - c.y);
	factor_b = b.x * (c.y - a.y);
	factor_c = c.x * (a.y - b.y);
	return (0.5 * fabsf(factor_a + factor_b + factor_c));
}

/**
	* calculate_angle - Counts angle between two points
*/
