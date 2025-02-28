#include "./fdf.h"
#define FILE_ERROR "Failed to open map file"
#define BUFFER_SIZE 256
/**
 * ft_min - Returns the min value of two given
 */
static size_t	ft_min(size_t a, size_t b) {
	if (a < b)
		return (a);
	return (b);
}


/**
 * ft_realloc - Mimics the behavior of realloc
 * @old: old block to reallocate
 * @old_size: Old block size
 * @new_size:  The new requested size
 * Return: New block or NULL if errors occured
 */
void	*ft_realloc(void *old,size_t old_size, size_t new_size)
{

	void	*new;

	if (!old)
		return (NULL);
	if (new_size == 0)
	{
		free(old);
		return (NULL);
	}
	new = malloc(new_size + 1);
	if (!new)
		return (NULL);
	ft_bzero(new, new_size + 1);
	ft_memcpy(new, old, ft_min(new_size, old_size));
	free(old);
	return (new);
}

/**
* read_file - Reads from a given filename
* Return: The buffer read from file or quits if errors
* occured
*/
char *read_file(char *filename)
{
	size_t	fd;
	size_t	idx;
	size_t	total_size;
	char	*buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(FILE_ERROR);
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
