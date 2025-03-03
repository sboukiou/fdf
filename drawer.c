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

/**
 * draw_line - draws a line segement based on two endpoints
 * @session: mlx session
 * @x1, y1: Coordinates of a
 * @x2, y2: Coordinates of b
 * Return: SUCCESS if it succeeded, or FAIL otherwise
 */
void draw_line(t_mlx_session *session, int x1, int y1, int x2, int y2) 
{ 
    int m_new = 2 * (y2 - y1); 
    int slope_error_new = m_new - (x2 - x1); 
    for (int x = x1, y = y1; x <= x2; x++) { 
		mlx_put_to_image(session->img, x, y, GREEN);
  
        /*Add slope to increment angle formed */
        slope_error_new += m_new; 
  
        /*Slope error reached limit, time to */
        /*increment y and update slope error. */
        if (slope_error_new >= 0) { 
            y++; 
            slope_error_new -= 2 * (x2 - x1); 
        } 
    } 
} 


/**
 * draw_map_cordinates - Draws Map points based on their given cordinates
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int	draw_map_cordinates(t_mlx_session *session, char ***map)
{
	int	z;

	if (!session || !session->img)
		return (FAIL);
	if (!map)
		return (FAIL);
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			z = ft_atoi(map[i][j]);
			int x = (j - z) / sqrt(2);
			int y = (j + 2 * i + z) / sqrt(6);
			mlx_put_to_image(session->img, x, y, GREEN);
		}
	}
	free_double_list(map);
	return (SUCCESS);
}

