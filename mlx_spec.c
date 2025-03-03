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
		exit(0);
	}
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

	offset = y * img->line_size + x * (img->bits_per_pixel / 8);

	dst = img->addr + offset;
	*(unsigned int*)dst = color;
}


