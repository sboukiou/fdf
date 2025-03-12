/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:09:20 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/12 00:45:51 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	get_z_color(t_point *origin)
{
	char	**items;

	items = ft_split(origin->values, ",");
	if (!items)
		return ;
	origin->z = ft_atoi(items[0]);
	origin->color = get_color(items[1]);
	if (!items[1])
	{
		if (origin->z)
			origin->color = DEFAULT_Z;
		else
			origin->color = DEFAULT;
	}
	free_list(items);
}

void	draw_line(t_session *session, t_point origin, t_point dest)
{
	get_z_color(&origin);
	get_z_color(&dest);
	origin.y = origin.y * cos(session->moves.rotate)
		- origin.z * sin(session->moves.rotate);
	origin.z = origin.y * sin(session->moves.rotate)
		+ origin.z * cos(session->moves.rotate);
	dest.y = dest.y * cos(session->moves.rotate)
		- dest.z * sin(session->moves.rotate);
	dest.z = dest.y * sin(session->moves.rotate)
		+ dest.z * cos(session->moves.rotate);
	iso_project(&origin, session->mapinfo.params, session);
	iso_project(&dest, session->mapinfo.params, session);
	bresenham_draw(origin, dest, session);
}
