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
# define MAP_SIZE 6


char	***check_map(int ac, char **av)
{
	int		(file_des), (inc);
	char	(*line_read), (***map);

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
	map = (char ***)ft_calloc(MAP_SIZE + 1, sizeof(char **));
	if (!map)
	{
		ft_printf("[ERROR]: Failed to allocate map size\n");
		exit(1);
	}
	inc = 0;
	while ((line_read = read_line(file_des)) != NULL)
	{
		map[inc] = ft_split(line_read, " \n");
		if (inc > 0 && list_len(map[0]) != list_len(map[inc]))
		{
			ft_printf("[ERROR]: Found wrong line length. Exiting.\n");
			free(line_read);
			free_double_list(map);
			exit(1);
		}
		inc++;
		if (inc >= MAP_SIZE && (inc) % MAP_SIZE == 0)
			map = (char ***)ft_realloc(map, inc * (sizeof(char **)), (inc + MAP_SIZE) * sizeof(char **));
		free(line_read);
	}
	if (inc == 0)
	{
		free_double_list(map);
		free(line_read);
		ft_printf("[ERROR]: No data found\n");
		exit(0);
	}
	map[inc] = NULL;
	close(file_des);
	return (map);
}

/**
	* main - Starting point of the program
	* @ac: Number of given arguments
	* @av: given args as array of strings
	* @Return: 0 on sucess
	*/
int main(int ac, char **av)
{
	return (0);
}
