/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 05:17:28 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/02 05:17:35 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include <X11/keysym.h>
/**
	* handle_key - Check if a given key is the escape
	* @key_code: The number corresponding to the key
	* @data: Info about the mlx and mlx_window ptrs
	* @Return: 0 , Or quit berfore if it's ESC
	*/
int	handle_key(int key_code, t_mlx_session *mlx_session)
{
	if (key_code == ESCAPE)
	{
		mlx_destroy_image(mlx_session->mlx, mlx_session->img->img);
		mlx_destroy_window(mlx_session->mlx, mlx_session->mlx_win);
		mlx_destroy_display(mlx_session->mlx);
		free(mlx_session->mlx);
		free_double_list(mlx_session->mapinfo.map);
		exit(0);
	}
	if (key_code == XK_k)
		mlx_session->moves.y -= 15;
	if (key_code == XK_h)
		mlx_session->moves.x -= 15;
	if (key_code == XK_j)
		mlx_session->moves.y += 15;
	if (key_code == XK_l)
		mlx_session->moves.x += 15;
	if (key_code == XK_i)
		mlx_session->moves.zoom += 0.1;
	if (key_code == XK_o && mlx_session->mapinfo.params.scale >= 0)
		mlx_session->moves.zoom -= 0.1;
	if (key_code == XK_p)
		mlx_session->moves.parallel = 1;
	if (key_code == XK_s)
		mlx_session->moves.parallel = 0;
	if (key_code == XK_r)
		mlx_session->moves.rotate += 0.098;
	if (key_code == XK_z)
		mlx_session->moves.z += 1;
	if (key_code == XK_a)
		mlx_session->moves.z -= 1;

	mlx_destroy_image(mlx_session->mlx, mlx_session->img->img);
	mlx_session->img->img = mlx_new_image(mlx_session->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_shape(mlx_session, mlx_session->mapinfo);
	mlx_put_image_to_window(mlx_session->mlx, mlx_session->mlx_win, mlx_session->img->img, 0, 0);
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
	*(unsigned int*)dst = color;
}

int		quit_mlx_session(t_mlx_session *session)
{
	mlx_destroy_image(session->mlx, session->img->img);
	mlx_destroy_window(session->mlx, session->mlx_win);
	mlx_destroy_display(session->mlx);
	free(session->mlx);
	exit(0);
}
