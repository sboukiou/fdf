#include "./fdf.h"
#include <stdio.h>

int main(int ac, char **av)
{
	if (parser(ac, av) == FAIL)
		ft_printf("Map is invalid\n");
	else
		ft_printf("Map is valid\n");
	return (0);
}
