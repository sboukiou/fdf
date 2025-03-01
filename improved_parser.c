/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improved_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:32:23 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/01 19:54:23 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

# define MAP_HEIGHT 1080
# define MAP_WIDTH 1920

void	free_map(t_pt	**map)
{
	size_t	idx;

	if (!map)
		return ;
	idx = 0;
	while (map[idx])
	{
		free(map[idx]);
		idx++;
	}
	free(map);
}

t_pt	**get_full_map(int ac, char **av)
{
	t_pt	**map;
	int		fd, atoi_temp;
	size_t	i,j, line_len;
	char	*line_read, **tokens, **value_data;

	if (ac != 2)
		return (ft_printf("USAGE: ./fdf [MAP_FILE]\n"), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("[ERRROR]: Failed to open map file\n"), NULL);
	line_read = read_line(fd);
	line_len = 0;
	map = (t_pt **)ft_calloc(MAP_HEIGHT + 1, sizeof(t_pt *));
	if (!map)
		return (ft_printf("[ERROR]: Failed to allocate map rows size\n"), NULL);
	i = 0;
	while (line_read != NULL)
	{
		tokens = ft_split(line_read, " \n");
		if (line_len && list_len(tokens) != line_len)
			return (free_list(tokens), free(line_read), free_map(map), ft_printf("[ERROR]: Lines sizes don't match\n"), NULL);
		if (line_len == 0)
			line_len = list_len(tokens);
		if (line_len > MAP_WIDTH)
			return (free_list(tokens), free(line_read), free_map(map), ft_printf("[ERROR]: Map height is larger than window HEIGHT\n"), NULL);

		map[i] = (t_pt *)ft_calloc(line_len, sizeof(t_pt));
		if (!map[i])
			return (free_list(tokens), free(line_read), free_map(map), ft_printf("[ERROR]: Failed to allocate map colums size\n"), NULL);
		j = 0;
		while (tokens[j])
		{
			map[i][j].x = j;
			map[i][j].y = i;
			value_data = ft_split(tokens[j], ",");
			if (!value_data || list_len(value_data) > 2)
				return (free_list(tokens), free(line_read), free_map(map), ft_printf("[ERROR]: Failed to split value data\n"), NULL);
			atoi_temp = ft_atoi(value_data[0]);
			if (atoi_temp == -1 && ft_strcmp(value_data[0], "-1"))
				return (free_list(tokens), free_list(value_data), free(line_read), free_map(map), ft_printf("[ERROR]: Invalid number given\n"), NULL);
			if (atoi_temp < 0 && atoi_temp > WINDOW_HEIGHT)
				return (free_list(tokens), free_list(value_data), free(line_read), free_map(map), ft_printf("[ERROR]: Large cordinates value\n"), NULL);
			if (value_data[1] && check_color(value_data[1]) == FAIL)
				return (free_list(tokens), free_list(value_data), free(line_read), free_map(map), ft_printf("[ERROR]: Color format invalid\n"), NULL);

			free_list(value_data);
			map[i][j].z = atoi_temp;
			j++;
		}
		i++;
		free_list(tokens);
		free(line_read);
		if (i == MAP_HEIGHT)
			return (ft_printf("[ERROR]: Map height is larger than window HEIGHT\n"), NULL);
		line_read = read_line(fd);
	}
	map[i] = NULL;
	return (map);
}
