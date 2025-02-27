#include <mlx.h>

int main(void)
{
	void	*mlx;
	void	*mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Typical window");
	mlx_loop(mlx);
}
