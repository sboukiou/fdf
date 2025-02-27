#include "fdf.h"

void	terminate(char *code)
{
	write(STDOUT_FILENO, "Faile to establish mlx connection:", 35);
	write(STDOUT_FILENO, code, ft_strlen(code));
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

/**
	* handle_key - Check if a given key is the escape
	* @key_code: The number corresponding to the key
	* @data: Info about the mlx and mlx_window ptrs
	* @Return: 0 , Or quit berfore if it's ESC
*/

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

/**
	* main - Starting point of the program
	* @ac: Number of given arguments
	* @av: given args as array of strings
	* @Return: 0 on sucess
*/

int main(void)
{
	t_data	data;

	/*Initializing the mlx connection to the X server*/
	data.mlx = mlx_init();
	if (!data.mlx)
		terminate(MLX_INIT);
	/*Creating the window with size + title*/
	data.mlx_win= mlx_new_window(data.mlx, 1000, 1000, "Typical window");
	if (!data.mlx_win)
		terminate(MLX_WINDOW);
	/*Binding the keyPress with the handle_key function*/
	mlx_hook(data.mlx_win, KEY_PRESS_EVENT, KEY_PRESS_MASK, handle_key, &data);
	mlx_pixel_put(&data.mlx, &data.mlx_win, 5, 5, 0xFF0000);

	mlx_loop(data.mlx);
	return (0);
}
