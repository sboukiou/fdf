/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:25:35 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/02 05:25:18 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

/**
 * draw_square - Draws a square with a corresponding sides
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int	draw_square(t_mlx_session *session)
{

	if (!session || !session->img)
		return (FAIL);
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for(int j = 0; j < WINDOW_WIDTH; j++)
		{
			mlx_put_to_image(session->img, j, i, GREEN);
		}
	}
	return (SUCCESS);
}

/**
 * draw_circle - Draws a circle with a corresponding radius
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int	draw_circle(t_mlx_session *session)
{
	if (!session || !session->img)
		return (FAIL);
	for (int i = 0; i < 300; i ++)
	{
		for (int j = 0; j < 300; j++)
			if (j == 0 || j == 299 || i == 0 || i == 299)
				mlx_put_to_image(session->img, j + SCALE, i + SCALE, GREEN);
	}
	return (SUCCESS);
}

int draw_line(t_mlx_session *session, int x1, int y1, int x2, int y2, int color)
{
	t_pt	a, b, cords;
	a.x =  x1;
	b.x =  x2;
	a.y =  y1;
	b.y =  y2;
	for (int i = ft_min(y1, y2); i < ft_max(y1, y2); i++)
	{
		for (int j = ft_min(x1, x2); j < ft_max(x1, x2); j++)
		{
			cords.x = j;
			cords.y = i;
			if (triangle_area(a, b, cords) == 0)
				mlx_put_to_image(session->img, j, i, color);
		}
	}
	return (0);
}

