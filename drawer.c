/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:25:35 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 22:08:51 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	set_params(t_session *session, t_parameters *params)
{
	t_point	projection;
	int		i;
	int		j;

	i = 0;
	while (session->mapinfo.map[i])
	{
		j = 0;
		while (session->mapinfo.map[i][j])
		{
			projection.x = j;
			projection.y = i;
			projection.z = atoi(session->mapinfo.map[i][j++]);
			iso_project(&projection, *params, session);
			if (params->min_width > projection.x)
				params->min_width = projection.x;
			if (params->min_height > projection.y)
				params->min_height = projection.y;
			if (params->max_width < projection.x)
				params->max_width = projection.x;
			if (params->max_height < projection.y)
				params->max_height = projection.y;
		}
		i++;
	}
}

static t_parameters	get_parameters(t_session *session)
{
	t_parameters	params;
	float			scale_x;
	float			scale_y;

	params.min_width = INT_MAX;
	params.min_height = INT_MAX;
	params.max_width = INT_MIN;
	params.max_height = INT_MIN;
	params.scale = 1;
	set_params(session, &params);
	scale_x = (WIN_WIDTH * 0.25) / (params.max_width - params.min_width);
	scale_y = (WIN_HEIGHT * 0.25) / (params.max_height - params.min_height);
	if (scale_x > scale_y)
		params.scale = scale_y;
	else
		params.scale = scale_x;
	params.scale += session->moves.zoom;
	params.offset_x = (WIN_WIDTH) / 2 + session->moves.x;
	params.offset_y = (WIN_HEIGHT) / 2 + session->moves.y;
	return (params);
}

/**
 * draw_line - draws a line segement based on two endpoints
 * @session: mlx session
 * @x1, y1: Coordinates of a
 * @x2, y2: Coordinates of b
 * Return: SUCCESS if it succeeded, or FAIL otherwise
 */

void	pick_drawers(t_session *session, t_mapinfo mapinfo, t_point origin)
{
	t_point	point_a;
	t_point	point_b;
	int		i;
	int		j;

	i = origin.y;
	j = origin.x;
	if (mapinfo.map[i + 1])
	{
		point_a.x = j;
		point_a.y = i + 1;
		point_a.values = mapinfo.map[i + 1][j];
		draw_line(session, origin, point_a);
	}
	if (mapinfo.map[i][j + 1])
	{
		point_b.x = j + 1;
		point_b.y = i;
		point_b.values = mapinfo.map[i][j + 1];
		draw_line(session, origin, point_b);
	}
}

void	draw_shape(t_session *session, t_mapinfo mapinfo)
{
	t_point	origin;
	int		i;
	int		j;

	i = 0;
	session->mapinfo.params = get_parameters(session);
	while (mapinfo.map[i])
	{
		j = 0;
		while (mapinfo.map[i][j])
		{
			origin.x = j;
			origin.y = i;
			origin.z = 0;
			origin.color = WHITE;
			origin.values = mapinfo.map[i][j];
			pick_drawers(session, mapinfo, origin);
			j++;
		}
		i++;
	}
}
