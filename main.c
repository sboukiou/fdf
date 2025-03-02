/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:03:30 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/02 05:19:16 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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
		return (ft_printf("[ERROR]: Failed to init mlx session\n"), 0);
	mlx_session.mlx_win= mlx_new_window(mlx_session.mlx,
						WINDOW_WIDTH, WINDOW_HEIGHT, "Typical window");
	if (!mlx_session.mlx_win)
		return (ft_printf("[ERROR]: Failed to init mlx window\n"), 0);
	img.img = mlx_new_image(mlx_session.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	mlx_session.img = &img;
	draw_circle(&mlx_session);
	mlx_put_image_to_window(mlx_session.mlx, mlx_session.mlx_win, img.img, 0, 0);
	mlx_hook(mlx_session.mlx_win, KEY_PRESS_EVENT, KEY_PRESS_MASK, handle_key, &mlx_session);
	mlx_loop(mlx_session.mlx);
	return (0);
}
