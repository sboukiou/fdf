#include "fdf.h"
#include <stdlib.h>

int	handle_key(int key_code, t_data *data)
{
	if (key_code == ESCAPE)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	return (0);
}

int main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.mlx_win= mlx_new_window(data.mlx, 1000, 1000, "Typical window");
	mlx_key_hook(data.mlx_win, &handle_key, &data);

	mlx_loop(data.mlx);
	return (0);
}
