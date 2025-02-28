#include "./fdf.h"


int main(int ac, char **av)
{
	char	*file_content;

	if (ac != 2)
	{
		ft_printf("Args count invalid\n");
		exit(0);
	}
	file_content = read_file(av[1]);
	ft_printf("-----------------------------\n%s\n-----------------------------\n", file_content);
	free(file_content);
	return (0);
}
