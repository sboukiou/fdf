#include "./fdf.h"
#include <stdio.h>

int main(int ac, char **av)
{
	char	***map;

	map = parser(ac, av);
	if (map == NULL)
		ft_printf("Map is invalid\n");
	else
		ft_printf("Map is valid\n");
	free_double_list(map);
	return (0);
}
