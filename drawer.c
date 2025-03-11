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

void	iso_project(t_point *pt, t_parameters params, t_session *session)
{
	int (pos_x), (pos_y);
	float (angle);
	angle = M_PI / 6;
	pos_x = (pt->x - pt->y) * cos(angle) * params.scale;
	pos_y = (pt->x + pt->y) * sin(angle) * params.scale - fabsf(pt->z * params.scale);
	if (session->moves.parallel == 0)
	{
		pt->x = abs(pos_x + params.offset_x);
		pt->y = abs(pos_y + params.offset_y);
	}
	else
{
		pt->x = fabsf(pt->x * (params.scale)) + params.offset_x;
		pt->y = fabsf(pt->y * (params.scale)) + params.offset_y;
	}
}

static t_parameters	get_parameters(t_session *session)
{
	float	(scale_x), (scale_y);
	t_point	(projection);
	t_point	(center);
	t_parameters	params;

	params.min_width = INT_MAX;
	params.min_height = INT_MAX;
	params.max_width = INT_MIN;
	params.max_height = INT_MIN;
	params.scale = 1;
	for (int i = 0; session->mapinfo.map[i]; i++)
	{
		for (int j = 0; session->mapinfo.map[i][j]; j++)
		{
			projection.x = j;
			projection.y = i;
			projection.z = atoi(session->mapinfo.map[i][j]);
			iso_project(&projection, params, session);
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
	scale_x = (WIN_WIDTH * 0.25) / (params.max_width - params.min_width);
	scale_y = (WIN_HEIGHT * 0.25) / (params.max_height - params.min_height);
	if (scale_x > scale_y)
		params.scale = scale_y;
	else
		params.scale = scale_x;
	params.scale += session->moves.zoom;
	center.x = (params.max_width - params.min_width);
	center.y = (params.max_height - params.min_height);
	(void)center;
	params.offset_x = (WIN_WIDTH) / 2 + session->moves.x;
	params.offset_y = (WIN_HEIGHT) / 2 + session->moves.y;
	return (params);
}

void 	bresenham_draw(t_point origin, t_point dest, t_session *session)
{
	int dx = abs(dest.x - origin.x);
	int dy = -abs(dest.y - origin.y);
	int sx = origin.x < dest.x ? 1 : -1;
	int sy = origin.y < dest.y ? 1 : -1;
	int err = dx + dy;
	int e2;
	while (origin.x != dest.x || origin.y != dest.y) {
		if (origin.x > 0 && origin.y > 0)
			mlx_put_to_image(session->img, origin.x, origin.y, origin.color);

		e2 = 2 * err;
		if (e2 >= dy) {
			if (origin.x == dest.x) {
				break;
			}
			err += dy;
			origin.x += sx;
		}
		if (e2 <= dx) {
			if (origin.y == dest.y) {
				break;
			}
			err += dx;
			origin.y += sy;
		}
	}
	if (origin.x > 0 && origin.y > 0)
		mlx_put_to_image(session->img, origin.x, origin.y, origin.color);
}

/**
 * draw_line - draws a line segement based on two endpoints
 * @session: mlx session
 * @x1, y1: Coordinates of a
 * @x2, y2: Coordinates of b
 * Return: SUCCESS if it succeeded, or FAIL otherwise
 */

static void draw_line(t_session *session,t_point origin, t_point dest, t_parameters params)
{
	char	**items;

	items = ft_split(origin.values, ",");
	origin.z = ft_atoi(items[0]);
	origin.color = get_color(items[1]);
	if (!items[1])
	{
		if (origin.z)
			origin.color = DEFAULT_Z;
		else
			origin.color = DEFAULT;
	}
	free_list(items);

	items = ft_split(dest.values, ",");
	dest.z = ft_atoi(items[0]);
	dest.color = get_color(items[1]);
	if (!items[1])
	{
		if (dest.z)
			dest.color = DEFAULT_Z;
		else
			dest.color = DEFAULT;
	}
	free_list(items);

	iso_project(&origin, params, session);
	iso_project(&dest, params, session);
	if (session->moves.rotate)
	{
		origin.y = origin.y * cos(session->moves.rotate) - origin.z * sin(session->moves.rotate);
		origin.z = origin.y * sin(session->moves.rotate) + origin.z;
		dest.y = dest.y * cos(session->moves.rotate) - dest.z * sin(session->moves.rotate);
		dest.z = dest.y * sin(session->moves.rotate) + dest.z;
	}
	bresenham_draw(origin, dest, session);

}


void	draw_shape(t_session *session, t_mapinfo mapinfo)
{
	int	(i), (j);
	t_point			origin;
	t_point			point_b;
	t_point			point_a;
	i = 0;
	session->mapinfo.params = get_parameters(session);
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
				draw_line(session, origin, point_a, session->mapinfo.params);
			}
			if (mapinfo.map[i][j + 1])
			{
				point_b.x = j + 1;
				point_b.y = i;
				point_b.values = mapinfo.map[i][j + 1];
				draw_line(session, origin, point_b, session->mapinfo.params);
			}
			j++;
		}
		i++;
	}
}
