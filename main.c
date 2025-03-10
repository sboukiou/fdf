/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:03:30 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/06 20:24:38 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define SUCCESS 0
# define FAIL -1
# define MAP_SIZE 1024


t_mapinfo	check_map(int ac, char **av)
{
	int		(file_des), (inc);
	char	(*line_read);
	size_t	line_len;
	t_mapinfo	mapinfo;

	if (ac != 2)
	{
		ft_printf("[Usage] : %s <filename> [ case_size z_size ]\n", av[0]);
		exit(1);
	}
	if ((file_des = open(av[1], O_RDONLY)) == FAIL)
	{
		ft_printf("[ERROR]: No file %s\n", av[1]);
		exit(1);
	}
	mapinfo.map = (char ***)ft_calloc(MAP_SIZE + 1, sizeof(char **));
	if (!mapinfo.map)
	{
		ft_printf("[ERROR]: Failed to allocate map size\n");
		exit(1);
	}
	inc = 0;
	while ((line_read = read_line(file_des)) != NULL)
	{
		mapinfo.map[inc] = ft_split(line_read, " \n");
		if (inc == 0)
			line_len = list_len(mapinfo.map[inc]);
		if (list_len(mapinfo.map[inc]) < line_len)
		{
			ft_printf("[ERROR]: Found wrong line length. Exiting.\n");
			free(line_read);
			free_double_list(mapinfo.map);
			exit(1);
		}
		inc++;
		if (inc >= MAP_SIZE && (inc) % MAP_SIZE == 0)
			mapinfo.map = (char ***)ft_realloc(mapinfo.map, inc * (sizeof(char **)), (inc + MAP_SIZE) * sizeof(char **));
		free(line_read);
	}
	if (inc == 0)
	{
		free_double_list(mapinfo.map);
		free(line_read);
		ft_printf("[ERROR]: No data found\n");
		exit(0);
	}
	mapinfo.map[inc] = NULL;
	close(file_des);
	return (mapinfo);
}

/**
	* main - Starting point of the program
	* @ac: Number of given arguments
	* @av: given args as array of strings
	* @Return: 0 on sucess
	*/
int main(int ac, char **av)
{
	t_mapinfo	mapinfo;
	t_mlx_session	session;
	t_img_data		img;
	mapinfo = check_map(ac, av);
	session.mlx = mlx_init();
	session.mlx_win = NULL;
	session.moves.up = 0;
	session.moves.down = 0;
	session.moves.left = 0;
	session.moves.right = 0;
	session.moves.zoom_in = 0;
	session.moves.zoom_out = 0;
	if (!session.mlx)
	{
		ft_printf("[ERROR]: Failed to init mlx connection\n");
		exit(1);
	}
	session.mlx_win = mlx_new_window(session.mlx, WIN_WIDTH, WIN_HEIGHT, "Mlx_window");
	if (!session.mlx_win)
	{
		ft_printf("[ERROR]: Failed to creat mlx window\n");
		exit(1);
	}
	img.img = mlx_new_image(session.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	session.img = &img;
	session.mapinfo = mapinfo;
	draw_shape(&session, mapinfo);
	mlx_put_image_to_window(session.mlx, session.mlx_win, session.img->img, 0, 0);
	mlx_hook(session.mlx_win, KEY_PRESS_EVENT, KEY_PRESS_MASK, handle_key, &session);
	mlx_loop(session.mlx);
	return (0);
}
