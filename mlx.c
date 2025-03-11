/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:17:28 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 23:46:10 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include <X11/keysym.h>

void	handle_events(t_session *session, int key_code)
{
	if (key_code == XK_k)
		session->moves.y -= 5;
	if (key_code == XK_h)
		session->moves.x -= 5;
	if (key_code == XK_j)
		session->moves.y += 5;
	if (key_code == XK_l)
		session->moves.x += 5;
	if (key_code == XK_i)
		session->moves.zoom += 0.3;
	if (key_code == XK_o && session->mapinfo.params.scale >= 0)
		session->moves.zoom -= 0.3;
	if (key_code == XK_p)
	{
		session->moves.parallel = 1;
		session->moves.rotate = 0;
	}
	if (key_code == XK_s)
		session->moves.parallel = 0;
	if (key_code == XK_r)
		session->moves.rotate += 0.98;
	if (key_code == XK_e)
		session->moves.rotate -= 0.98;
}

/**
	* handle_key - Check if a given key is the escape
	* @key_code: The number corresponding to the key
	* @data: Info about the mlx and mlx_window ptrs
	* @Return: 0 , Or quit berfore if it's ESC
	*/
int	handle_key(int key_code, t_session *session)
{
	if (key_code == ESCAPE)
	{
		mlx_destroy_image(session->mlx, session->img->img);
		mlx_destroy_window(session->mlx, session->mlx_win);
		mlx_destroy_display(session->mlx);
		free(session->mlx);
		free_double_list(session->mapinfo.map);
		exit(0);
	}
	handle_events(session, key_code);
	if (key_code == XK_Tab)
	{
		session->moves.rotate = 0;
		session->moves.parallel = 0;
		session->moves.x = 0;
		session->moves.y = 0;
		session->moves.zoom = 0;
	}
	mlx_destroy_image(session->mlx, session->img->img);
	session->img->img = mlx_new_image(session->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_shape(session, session->mapinfo);
	mlx_put_image_to_window(session->mlx,
		session->mlx_win, session->img->img, 0, 0);
	return (0);
}

/**
 * mlx_put_to_image - Draws a pixel into an image using image address
 * increamented byt offset
 * @img_data - Struct holding the img info, addr, bpp, line_size ...
 * @x, @y: Cordinates of the pixed we want to draw
 * @color: Color to put pixel with
 */

void	mlx_put_to_image(t_img_data *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (y >= WIN_HEIGHT || x >= WIN_WIDTH)
		return ;
	offset = y * img->line_size + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

int	quit_session(t_session *session)
{
	mlx_destroy_image(session->mlx, session->img->img);
	mlx_destroy_window(session->mlx, session->mlx_win);
	mlx_destroy_display(session->mlx);
	free(session->mlx);
	exit(0);
}
