/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:21:56 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 23:42:33 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

#define BUFFER_SIZE 256

char	*read_line(int fd)
{
	size_t	idx;
	size_t	total_size;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	idx = 1;
	total_size = BUFFER_SIZE;
	if (read(fd, buffer, 1) != 1)
		return (free(buffer), NULL);
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
