/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:25:35 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/08 20:51:59 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	get_color(char *str)
{
	int	color;

	color = WHITE;
	if (!str)
		return (color);
	if (ft_strlen(str) < 3)
		return (color);
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (color);
	if (str[1] == 'x')
		color = handle_hex_lower(str);
	else if (str[1] == 'X')
		color = handle_hex_upper(str);
	return (color);
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

static t_parameters	get_parameters(char ***map)
{
	float	(scale_x), (scale_y);
	t_point	(projection);
	t_point	(center);
	t_parameters	params;

	params.min_width = INT_MAX;
	params.min_height = INT_MAX;
	params.max_width = INT_MIN;
	params.max_height = INT_MIN;
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			projection.x = j;
			projection.y = i;
			iso_project(&projection.x, &projection.y, atoi(map[i][j]), 1);
			if (params.min_width > projection.x)
				params.min_width = projection.x;
			if (params.min_height > projection.y)
				params.min_height = projection.y;
			if (params.max_width < projection.x)
				params.max_width = projection.x;
			if (params.max_height < projection.y)
				params.max_height = projection.y;
		}
	}
	scale_x = (WIN_WIDTH * 0.60) / (params.max_width - params.min_width);
	scale_y = (WIN_HEIGHT * 0.60) / (params.max_height - params.min_height);
	if (scale_x > scale_y)
		params.scale = scale_y;
	else
		params.scale = scale_x;
	center.x = (params.max_width - params.min_width);
	center.y = (params.max_height - params.min_height);
	params.offset_x = (WIN_WIDTH) / 4 + center.x;
	params.offset_y = (WIN_HEIGHT) / 4 + center.y;
	return (params);
}

/**
 * draw_line - draws a line segement based on two endpoints
 * @session: mlx session
 * @x1, y1: Coordinates of a
 * @x2, y2: Coordinates of b
 * Return: SUCCESS if it succeeded, or FAIL otherwise
 */

static void draw_line(t_mlx_session *session,t_point origin, t_point dest, t_parameters params)
{
	char	**items;

	items = ft_split(origin.values, ",");
	origin.z = atoi(items[0]);
	origin.color = get_color(items[1]);
	free_list(items);

	items = ft_split(dest.values, ",");
	dest.z = atoi(items[0]);
	dest.color = get_color(items[1]);
	free_list(items);

	iso_project(&origin.x, &origin.y, origin.z, params.scale);
	iso_project(&dest.x, &dest.y, dest.z, params.scale);
    int dx = abs(dest.x - origin.x);
    int dy = abs(dest.y - origin.y);
   int sx = (origin.x < dest.x) ? 1 : -1;
    int sy = (origin.y < dest.y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // Draw the pixel

        // If we've reached the destination point, stop
        if (origin.x == dest.x && origin.y == dest.y) break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            origin.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            origin.y += sy;
        }
        mlx_put_to_image(session->img, abs(origin.x + params.offset_x), abs(origin.y + params.offset_y), origin.color);
		if (origin.color < dest.color)
			origin.color--;
		else if (origin.color > dest.color)
			origin.color++;
	}
}

void	draw_shape(t_mlx_session *session, t_mapinfo mapinfo)
{
	int	(i), (j);
	t_point			origin;
	t_point			point_b;
	t_point			point_a;
	i = 0;
	mapinfo.params = get_parameters(mapinfo.map);
	while (mapinfo.map[i])
	{
		j = 0;
		while (mapinfo.map[i][j])
		{
			origin.x = j;
			origin.y = i;
			origin.values = mapinfo.map[i][j];
			if (mapinfo.map[i + 1])
			{
				point_a.x = j;
				point_a.y = i + 1;
				point_a.values = mapinfo.map[i + 1][j];
				draw_line(session, origin, point_a, mapinfo.params);
			}
			if (mapinfo.map[i][j + 1])
			{
				point_b.x = j + 1;
				point_b.y = i;
				point_b.values = mapinfo.map[i][j + 1];
				draw_line(session, origin, point_b, mapinfo.params);
			}
			j++;
		}
		i++;
	}
}
