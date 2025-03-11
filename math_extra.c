/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:41:23 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 23:41:59 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	distance(int x1, int y1, int x2, int y2)
{
	return (pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
