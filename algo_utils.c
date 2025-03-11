/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:50:42 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 22:20:26 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	init_bresenham(t_bresenham_params *bp, t_point or, t_point d)
{
	bp->dx = abs(d.x - or.x);
	bp->dy = -abs(d.y - or.y);
	bp->sx = -1;
	bp->sy = -1;
	if (or.x < d.x)
		bp->sx = 1;
	if (or.y < d.y)
		bp->sy = 1;
	bp->err = bp->dx + bp->dy;
}

void	bresenham_draw(t_point origin, t_point dest, t_session *session)
{
	t_bresenham_params	bp;

	init_bresenham(&bp, origin, dest);
	while (origin.x != dest.x || origin.y != dest.y)
	{
		if (origin.x > 0 && origin.y > 0)
			mlx_put_to_image(session->img, origin.x, origin.y, origin.color);
		bp.e2 = 2 * bp.err;
		if (bp.e2 >= bp.dy)
		{
			if (origin.x == dest.x)
				break ;
			bp.err += bp.dy;
			origin.x += bp.sx;
		}
		if (bp.e2 <= bp.dx)
		{
			if (origin.y == dest.y)
				break ;
			bp.err += bp.dx;
			origin.y += bp.sy;
		}
	}
	if (origin.x > 0 && origin.y > 0)
		mlx_put_to_image(session->img, origin.x, origin.y, origin.color);
}

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
	pos_y = (pt->x + pt->y) * sin(angle) * params.scale
		- fabsf(pt->z * params.scale);
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
