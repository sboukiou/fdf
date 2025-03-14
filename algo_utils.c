/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:50:42 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/12 00:02:11 by sboukiou         ###   ########.fr       */
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
	(void)params;
	if (pt->x * session->moves.zoom >= 0)
		pt->x *= (session->moves.zoom);
	if (pt->y * session->moves.zoom >= 0)
		pt->y *= (session->moves.zoom);
	if (pt->z * session->moves.zoom >= 0)
		pt->z *= (session->moves.zoom);
	if (session->moves.parallel == 1)
	{
		pt->x = pt->x;
		pt->y = pt->y;
	}
	else
	{
		pt->x = (pt->x - pt->y) * cos(0.8);
		pt->y = (pt->x + pt->y) * sin(0.8) - pt->z;
	}
	pt->y = pt->y * cos(session->moves.rotate)
		- pt->z * sin(session->moves.rotate);
	pt->z = pt->y * sin(session->moves.rotate)
		+ pt->z * cos(session->moves.rotate);
	pt->x += WIN_WIDTH / 2 + session->moves.x;
	pt->y += WIN_HEIGHT / 4 + session->moves.y;
}
