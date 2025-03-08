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
 * draw_line - draws a line segement based on two endpoints
 * @session: mlx session
 * @x1, y1: Coordinates of a
 * @x2, y2: Coordinates of b
 * Return: SUCCESS if it succeeded, or FAIL otherwise
 */

void draw_line(t_mlx_session *session, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // Draw the pixel

        // If we've reached the destination point, stop
        if (x0 == x1 && y0 == y1) break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
        mlx_put_to_image(session->img, x0, y0, RED);  // White color for example
	}
}

static int	get_color(char *str)
{
	if (!str)
		return (WHITE);
	return (WHITE);
}

static void	iso_project(int *x, int *y, int z, float scale)
{
	int	(pos_x), (pos_y);
	float	(angle);

	angle = M_PI / 6;
	pos_x = (*x - *y) * cos(angle) * scale;
	pos_y = (*x + *y) * sin(angle) * scale - fabsf(z  * scale);
	*x = pos_x;
	*y = pos_y;
}

static float	get_scale(char ***map)
{
	int	(proj_x), (min_x), (max_x);
	int	(proj_y), (min_y), (max_y);
	float	(scale_x), (scale_y);

	min_x = INT_MAX;
	min_y = INT_MAX;
	max_x = INT_MIN;
	max_y = INT_MIN;
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			proj_x = j;
			proj_y = i;
			iso_project(&proj_x, &proj_y, atoi(map[i][j]), 1);
			if (min_x > proj_x)
				min_x = proj_x;
			if (min_y > proj_y)
				min_y = proj_y;
			if (max_x < proj_x)
				max_x = proj_x;
			if (max_y < proj_y)
				max_y = proj_y;
		}
	}
	scale_x = (WIN_WIDTH * 0.70) / (max_x - min_x);
	scale_y = (WIN_HEIGHT * 0.70) / (max_y - min_y);
	if (scale_x > scale_y)
		return (scale_y);
	return (scale_x);
}

static void	draw_point(t_mlx_session *session, int x, int y, char *details, float scale)
{
	char	(**items);
	int		(z), (color), (cord_x), (cord_y);

	items = ft_split(details, ",");
	z = ft_atoi(items[0]);
	color = get_color(items[1]);
	free_list(items);
	cord_x = x;
	cord_y = y;
	iso_project(&cord_x, &cord_y, z, scale);
	cord_x = abs(cord_x + WIN_WIDTH / 2);
	cord_y = fabs(cord_y + WIN_HEIGHT / 3.4);
	ft_printf("put img at %d %d\n", cord_x, cord_y);
	mlx_put_to_image(session->img, cord_x, cord_y, color);
}

void	draw_shape(t_mlx_session *session, char ***map)
{
	int	(i), (j);
	float	(scale);
	i = 0;
	scale = get_scale(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			draw_point(session, j, i, map[i][j], scale);
			j++;
		}
		i++;
	}
}
