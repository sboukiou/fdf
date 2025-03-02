/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:03:30 by sboukiou          #+#    #+#             */
/*   Updated: 2025/02/27 20:32:06 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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


/**
	* main - Starting point of the program
	* @ac: Number of given arguments
	* @av: given args as array of strings
	* @Return: 0 on sucess
	*/
int	main(int ac, char **av)
{
	t_mlx_session	mlx_session;
	t_img_data		img;
	(void)ac;
	(void)av;

	/*Initializing the mlx connection to the X server*/
	mlx_session.mlx = mlx_init();
	if (!mlx_session.mlx)
		terminate(MLX_INIT);
	mlx_session.mlx_win= mlx_new_window(mlx_session.mlx,
						WINDOW_WIDTH, WINDOW_HEIGHT, "Typical window");
	if (!mlx_session.mlx_win)
		terminate(MLX_WINDOW);
	img.img = mlx_new_image(mlx_session.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	mlx_put_to_image(&img, 5, 5, RED);
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		for(int j = 0; j < WINDOW_HEIGHT; j++)
		{
			mlx_put_to_image(&img, i, j, RED);
		}
	}
	mlx_put_image_to_window(mlx_session.mlx, mlx_session.mlx_win, img.img, 0, 0);
	mlx_session.img = &img;
	mlx_hook(mlx_session.mlx_win, KEY_PRESS_EVENT, KEY_PRESS_MASK, handle_key, &mlx_session);
	mlx_loop(mlx_session.mlx);
	return (0);
}
