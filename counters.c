/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:20:58 by sboukiou          #+#    #+#             */
/*   Updated: 2025/03/11 22:21:07 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

size_t	list_len(char **list)
{
	size_t	size;

	size = 0;
	if (!list)
		return (size);
	while (list[size])
		size++;
	return (size);
}

size_t	map_len(char ***map)
{
	size_t	size;

	size = 0;
	if (!map)
		return (size);
	while (map[size])
		size++;
	return (size);
}
