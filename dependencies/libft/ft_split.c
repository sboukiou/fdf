/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:16:43 by sboukiou          #+#    #+#             */
/*   Updated: 2024/10/27 21:40:54 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define TRUE 1
#define FALSE 0

/**
* Checks if a string contains a char
*/
static int	is_included(char *str, char c)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

/**
	* Creates a string from a begin bytes until a given
	* delimiters
	*/
static char	*ft_create_string(const char *str, char *spec)
{
	size_t	size;
	char	*buffer;

	if (!str)
		return (NULL);
	size = 0;
	while (str[size] && !is_included(spec, str[size]))
		size++;
	buffer = ft_calloc(size + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, str, size + 1);
	return (buffer);
}

static char	**free_all(char **list)
{
	int	index;

	index = 0;
	if (!list)
		return (NULL);
	while (list[index])
	{
		free(list[index]);
		index++;
	}
	free(list);
	return (NULL);
}

static char	**ft_allocate_list(const char *str, char *spec)
{
	char	**list;
	int		index;
	int		size;

	index = 0;
	size = 0;
	list = NULL;
	if (!str)
		return (NULL);
	while (str[index])
	{
		while (str[index] && is_included(spec, str[index]))
			index++;
		if (str[index])
			size++;
		while (str[index] && !is_included(spec, str[index]))
			index++;
	}
	list = ft_calloc(size + 1, sizeof(char *));
	return (list);
}

char	**ft_split(const char *str, char *spec)
{
	int		index;
	int		size;
	char	**list;

	index = 0;
	size = 0;
	list = ft_allocate_list(str, spec);
	if (!list)
		return (NULL);
	while (str[index])
	{
		while (str[index] && is_included(spec, str[index]))
			index++;
		if (str[index])
		{
			list[size] = ft_create_string(str + index, spec);
			if (list[size] == NULL)
				return (free_all(list));
			size++;
		}
		while (str[index] && !is_included(spec, str[index]))
			index++;
	}
	list[size] = NULL;
	return (list);
}
