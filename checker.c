#include "fdf.h"

static int	is_included_in_hex(char c)
{
	size_t	idx;
	char	*hex_chars;

	hex_chars = "0123456789ABCDEFabcdef";
	idx = 0;
	while (hex_chars[idx])
	{
		if (c == hex_chars[idx])
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

static int	is_hex(char *str)
{
	size_t	idx;

	if (!str)
		return (ft_printf("hex number NULL\n"), FALSE);
	if (ft_strlen(str) > 10)
		return (ft_printf("Hex code length too large\n"), FALSE);
	if (str[0] != '0' || str[1] != 'x')
		return (ft_printf("Hex number format error\n"), FALSE);
	idx = 2;
	while (str[idx])
	{
		if (is_included_in_hex(str[idx]) == FALSE)
			return (ft_printf("Non hex char spotted -> %c\n", str[idx]), FALSE);
		idx++;
	}
	return (TRUE);
}

static int	check_one_map_element(char *str)
{
	char	**list;

	if (!str)
		return (0);
	list = ft_split(str, ",");
	if (list_len(list) > 2)
		return (ft_printf("token length more than 2\n"), free_list(list), FAIL);
	if (ft_atoi(list[0]) == -1 && ft_strcmp(list[0], "-1"))
		return (ft_printf("wrong number char given\n"), free_list(list), FAIL);
	if (list[1] && is_hex(list[1]) == FALSE)
		return (free_list(list),  FAIL);
	free_list(list);
	return (SUCCESS);

}

int	check_map_elements(char ***map)
{
	size_t	idx;
	size_t	jdx;

	idx = 0;
	while (map[idx])
	{
		jdx = 0;
		while (map[idx][jdx])
		{
			if (check_one_map_element(map[idx][jdx]) == FAIL)
				return (FAIL);
			jdx++;
		}
		idx++;
	}
	return (SUCCESS);
}

