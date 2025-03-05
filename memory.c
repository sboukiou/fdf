#include "fdf.h"
void	free_double_list(char ***list)
{
	int	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
	{
		free_list(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
}

void	free_list(char **list)
{
	int	idx;

	idx = 0;
	while (list[idx])
	{
		free(list[idx]);
		list[idx] = NULL;
		idx++;
	}
	free(list);
}

/**
 * ft_realloc - Mimics the behavior of realloc
 * @old: old block to reallocate
 * @old_size: Old block size
 * @new_size:  The new requested size
 * Return: New block or NULL if errors occured
 */
void	*ft_realloc(void *old, size_t old_size, size_t new_size)
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

