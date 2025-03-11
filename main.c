/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:03:30 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 22:26:36 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	***check_args(int ac, char **av, int *fd)
{
	char	***map;

	if (ac != 2)
	{
		ft_printf("[Usage] : %s <filename> [ case_size z_size ]\n", av[0]);
		exit(1);
	}
	*fd = open(av[1], O_RDONLY);
	if (*fd == FAIL)
	{
		ft_printf("[ERROR]: No file %s\n", av[1]);
		exit(1);
	}
	map = (char ***)ft_calloc(MAP_SIZE + 1, sizeof(char **));
	if (!map)
	{
		ft_printf("[ERROR]: Failed to allocate map size\n");
		exit(1);
	}
	return (map);
}

void	process_line(t_mapinfo *mapinfo, char *line_read,
		int *inc, size_t *line_len)
{
	mapinfo->map[*inc] = ft_split(line_read, " \n");
	if (*inc == 0)
		*line_len = list_len(mapinfo->map[*inc]);
	if (list_len(mapinfo->map[*inc]) < *line_len)
	{
		ft_printf("[ERROR]: Found wrong line length. Exiting.\n");
		free(line_read);
		free_double_list(mapinfo->map);
		exit(1);
	}
	(*inc)++;
	if (*inc >= MAP_SIZE && (*inc) % MAP_SIZE == 0)
		mapinfo->map = (char ***)ft_realloc(mapinfo->map,
				*inc * (sizeof(char **)),
				(*inc + MAP_SIZE) * sizeof(char **));
	free(line_read);
}

t_mapinfo	check_map(int ac, char **av)
{
	int			file_des;
	int			inc;
	char		*line_read;
	size_t		line_len;
	t_mapinfo	mapinfo;

	inc = 0;
	mapinfo.map = check_args(ac, av, &file_des);
	line_read = read_line(file_des);
	while (line_read != NULL)
	{
		process_line(&mapinfo, line_read, &inc, &line_len);
		line_read = read_line(file_des);
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

static void	init_session_members(t_session *session)
{
	session->mlx_win = NULL;
	session->moves.x = 0;
	session->moves.y = 0;
	session->moves.zoom = 0;
	session->moves.parallel = 0;
	session->moves.rotate = 0;
	session->moves.z = 0;
}

/**
	* main - Starting point of the program
	* @ac: Number of given arguments
	* @av: given args as array of strings
	* @Return: 0 on sucess
	*/
int	main(int ac, char **av)
{
	t_session	session;
	t_img_data	img;

	session.mapinfo = check_map(ac, av);
	session.mlx = mlx_init();
	init_session_members(&session);
	if (!session.mlx)
		return (ft_printf("[ERROR]: Failed to init mlx connection\n"), 1);
	session.mlx_win = mlx_new_window(session.mlx,
			WIN_WIDTH, WIN_HEIGHT, "Mlx_window");
	if (!session.mlx_win)
		return (ft_printf("[ERROR]: Failed to creat mlx window\n"), 1);
	img.img = mlx_new_image(session.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	session.img = &img;
	draw_shape(&session, session.mapinfo);
	mlx_put_image_to_window(session.mlx,
		session.mlx_win, session.img->img, 0, 0);
	mlx_hook(session.mlx_win, KEY_PRESS_EVENT, 1L << 0, handle_key, &session);
	mlx_loop(session.mlx);
	return (0);
}
