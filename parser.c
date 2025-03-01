#include "./fdf.h"
#define FILE_FAIL "Failed to open map file"
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

/**
* read_file - Reads from a given filename
* Return: The buffer read from file or quits if errors
* occured
*/
char *read_file(char *filename)
{
	int	fd;
	size_t	idx;
	size_t	total_size;
	char	*buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(FILE_FAIL);
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	idx = 0;
	total_size = BUFFER_SIZE;
	while (read(fd, buffer + idx, 1) > 0)
	{
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

size_t	list_len(char **list)
{
	size_t	len;

	len = 0;
	while (list[len])
		len++;
	return (len);
}
int	parser(int ac, char **av)
{
	char	*file_read;
	char	**lines;
	char	***map;
	size_t	i;

	if (ac != 2)
	{
		ft_printf("args count invalid\n");
		exit(0);
	}
	file_read = read_file(av[1]);
	if (!file_read)
		return (ft_printf("reading failed\n"), FAIL);
	lines = ft_split(file_read, "\n");
	free(file_read);
	if (!lines)
		return (ft_printf("Allocation for lines failed\n"), FAIL);
	map = (char ***)ft_calloc(list_len(lines) + 1, sizeof(char **));
	if (!map)
		return (ft_printf("splitting lines into map tokens failed\n"), free_list(lines), FAIL);
	i = 0;
	while (lines[i])
	{
		map[i] = ft_split(lines[i], " ");
		if (!map[i] || (list_len(map[i]) != list_len(map[0])))
			return (ft_printf("Map lines lengths inequal\n"), free_list(lines), free_double_list(map), FAIL);
		i++;
	}
	if (check_map_elements(map) == FAIL)
		return (ft_printf("Map checking failed\n"), free_double_list(map), free_list(lines), FAIL);
	free_double_list(map);
	free_list(lines);
	return (SUCCESS);
}
