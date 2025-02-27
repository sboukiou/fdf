/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:52:32 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/27 19:55:23 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

# define RADIUS 9000

/**
 * draw_circle - Draws a circle with a corresponding radius
 * @session: Mlx session to draw in
 * @radius: Radius of the circle to draw
 * Return: 0 on success or -1 on errors
 */
int	draw_circle(t_mlx_session *session)
{
	t_pt	circle_center;
	t_pt	cords;

	if (!session->mlx)
		return (ERROR);
	circle_center.x = WINDOW_WIDTH / 2;
	circle_center.y = WINDOW_WIDTH / 2;
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			cords.x = j;
			cords.y = i;
			 if (distance(cords, circle_center) < RADIUS)
				mlx_pixel_put(session->mlx, session->mlx_win,
				i, j, RED);
		}
	}
	return (SUCESS);
}


