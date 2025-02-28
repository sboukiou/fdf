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
 * terminate - Ends the program with the corresponding message
 * @code: Error code to display
 */
void	terminate(char *code)
{
	write(STDOUT_FILENO, "Faile to establish mlx connection:", 35);
	write(STDOUT_FILENO, code, ft_strlen(code));
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

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
		mlx_destroy_window(mlx_session->mlx, mlx_session->mlx_win);
		mlx_destroy_display(mlx_session->mlx);
		free(mlx_session->mlx);
		exit(0);
	}
	return (0);
}

/**
	* main - Starting point of the program
	* @ac: Number of given arguments
	* @av: given args as array of strings
	* @Return: 0 on sucess
	*/
int	main(void)
{
	t_mlx_session	mlx_session;

	/*Initializing the mlx connection to the X server*/
	mlx_session.mlx = mlx_init();
	if (!mlx_session.mlx)
		terminate(MLX_INIT);
	/*Creating the window with size + title*/
	mlx_session.mlx_win= mlx_new_window(mlx_session.mlx,
						WINDOW_WIDTH, WINDOW_HEIGHT, "Typical window");
	if (!mlx_session.mlx_win)
		terminate(MLX_WINDOW);
	/*Binding the keyPress with the handle_key function*/
	mlx_hook(mlx_session.mlx_win, KEY_PRESS_EVENT, KEY_PRESS_MASK, handle_key, &mlx_session);
	/*mlx_pixel_put(&mlx_session.mlx, &mlx_session.mlx_win, 5, 5, 0xFF0000);*/
	mlx_loop_hook(mlx_session.mlx, draw_shapes, &mlx_session);

	mlx_loop(mlx_session.mlx);
	return (0);
}
