/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:25:35 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/28 01:25:37 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

#define RADIUS 9000

/**
 * draw_circle - Draws a circle with a corresponding radius
 * @session: Mlx session to draw in
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
				  j, i, RED);
		}
	}
	return (SUCCESS);
}

/**
 * draw_segement - Draws a line segement with a corresponding cords
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int draw_segement(t_mlx_session *session, t_pt a, t_pt b)
{
	t_pt	cords;

	if (!session->mlx)
		return (ERROR);
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			cords.x = j;
			cords.y = i;
			if (triangle_area(cords, a, b) == 0 &&
			distance(cords, a) + distance(cords, b) <= distance(a, b))
				mlx_pixel_put(session->mlx, session->mlx_win,
				  j, i, RED);
		}
	}
	return (SUCCESS);
}

/**
 * draw_line - Draws a line  with a corresponding cords
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int draw_line(t_mlx_session *session, t_pt a, t_pt b)
{
	t_pt	cords;

	if (!session->mlx)
		return (ERROR);
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			cords.x = j;
			cords.y = i;
			if (triangle_area(cords, a, b) == 0)
				mlx_pixel_put(session->mlx, session->mlx_win,
				  j, i, RED);
		}
	}
	return (SUCCESS);
}

/**
 * draw_shapes - Draws a given shapes according to functions
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int	draw_shapes(t_mlx_session *session)
{

	t_pt	x_seg;
	/*t_pt	y_seg;*/
	t_pt	z_seg;
	t_pt	center;

	center.x = WINDOW_WIDTH / 2;
	center.y = WINDOW_HEIGHT / 2;
	z_seg.x =  WINDOW_WIDTH / 2;
	z_seg.y = 0;
	x_seg.x = 0;
	x_seg.y = center.y;
	draw_segement(session, z_seg, center);
	draw_line(session, center, x_seg);
	return (SUCCESS);
}

