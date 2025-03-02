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
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for(int j = 0; j < WINDOW_WIDTH; j++)
		{
			if (abs(distance(j, i, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2) - 9000) < 200)
				mlx_put_to_image(session->img, j, i, GREEN);
		}
	}
	return (SUCCESS);
}

int	draw_line(t_mlx_session *session)
{
	
}

