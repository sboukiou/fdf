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
/**
 * draw_map_cordinates - Draws Map points based on their given cordinates
 * @session: Mlx session to draw in
 * Return: 0 on success or -1 on errors
 */
int draw_map_cordinates(t_mlx_session *session, char ***map)
{
    int z;
    float angle;
	int	scale_factor;
	int center_x;
	int center_y;
	int x;
	int y;
	int	x_scaled;
	int	y_scaled;
	int	x_screen;
	int	y_screen;

	if (!session || !session->img)
		return (FAIL);
	if (!map)
		return (FAIL);
	angle = M_PI / 6;
    // Scaling factor for bigger drawing
    scale_factor = 1;

    center_x = WINDOW_WIDTH / 2;
    center_y = WINDOW_HEIGHT / 4;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
		{
			z = atoi(map[i][j]);
			x = (j - i) * cos(angle); 
			y = (i + j) * sin(angle) - z;
			x_scaled = (int)(x * scale_factor);
			y_scaled = (int)(y * scale_factor);
			x_screen = x_scaled + center_x;
			y_screen = y_scaled + center_y;
			if (z)
				mlx_put_to_image(session->img, x_screen, y_screen, GREEN);
			else
				mlx_put_to_image(session->img, x_screen, y_screen, 0xFFFFFF);
			int z_down, z_right;
			if (map[i + 1])
				z_down = atoi(map[i + 1][j]);
			else
				z_down = 0;
			if (map[i][j + 1])
				z_right = atoi(map[i][j + 1]);
			else
				z_right = 0;
			int x_down = (int)(((j - i - 1) * cos(angle)) * scale_factor) + center_x;
			int y_down = (int)(((j + i + 1) * sin(angle) - z_down) * scale_factor) + center_y;
			int x_right = (int)(((j + 1 - i) * cos(angle)) * scale_factor) + center_x;
			int y_right = (int)(((j + i + 1) * sin(angle) - z_right) * scale_factor) + center_y;
			draw_line(session, x_screen, y_screen, x_right, y_right);
			draw_line(session, x_screen, y_screen, x_down, y_down);
		}
    }
    free_double_list(map);
    return (SUCCESS);
}
