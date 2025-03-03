#include "./fdf.h"

#define BUFFER_SIZE 256
/**
* read_line - Reads a line from a given filename
* Return: The line read from file or quits if errors
* occured
*/
char *read_line(int fd)
{
	size_t	idx;
	size_t	total_size;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	idx = 0;
	total_size = BUFFER_SIZE;
	while (read(fd, buffer + idx, 1) > 0)
	{
		if (buffer[idx] == '\n')
			return (buffer);
		idx++;
		if (idx == total_size)
		{
			total_size += BUFFER_SIZE;
			buffer = ft_realloc(buffer, idx, idx + BUFFER_SIZE);
		}
	}
	buffer = ft_realloc(buffer, idx + BUFFER_SIZE, idx);
	return (buffer);
}


char	***parser(int ac, char **av)
{
	char	***map, *line;
	int	fd;
	size_t	line_count;

	if (ac != 2)
		return (ft_printf("[ERROR]: Invalid number of arguments\n"), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("[ERROR]: Failed to open map file\n"), NULL);
	line = read_line(fd);
	if (!line)
		return (ft_printf("[ERROR]: Failed to read from map file or file empty\n"), NULL);
	line_count = 1;
	while (line)
	{
		free(line);
		line = read_line(fd);
		line_count++;
	}
	map = (char ***)ft_calloc(line_count, sizeof(char **));
	if (!map)
		return (ft_printf("[ERROR]: Faile to allocate map rows\n"), free(line), NULL);
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("[ERROR]: Failed to open map file\n"), NULL);
	line = read_line(fd);
	line_count = 0;
	while (line)
	{
		map[line_count] = ft_split(line, " \n");
		if (!map[line_count])
			return (ft_printf("[ERROR]: Faile to split line tokens\n"), free(line), free_double_list(map), NULL);
		free(line);
		line = read_line(fd);
		line_count++;
	}
	return (map);
}
