#include <math.h>
#include <mlx.h>


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct s_point_cords
{
	int x;
	int	y;
}	t_point_cords;

float	calculte_distance(t_point_cords center, t_point_cords pt)
{

	return (pow(center.x - pt.x, 2) +pow(center.y - pt.y, 2));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	t_point_cords center = {500, 500};
	t_point_cords	drawer;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!");
	img.img = mlx_new_image(mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int i = 0; i < 1000; i ++)
	{
		for (int j = 0; j < 1000; j++)
		{
			drawer.x = j;
			drawer.y = i;
			if (calculte_distance(center, drawer) <= 500)
				my_mlx_pixel_put(&img, i, j, 0x00FF0000);
			j++;
		}
		i++;
	}
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

