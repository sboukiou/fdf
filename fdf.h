#ifndef FDF_H
# define FDF_H

# include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

# include "dependencies/libft/libft.h"
# include "dependencies/ft_printf/ft_printf.h"

# define ESCAPE 65307
# define KEY_PRESS_EVENT 2
# define KEY_PRESS_MASK 1L<<0

# define MLX_INIT "MLX_INIT"
# define MLX_WINDOW "MLX_WINDOW"

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
}	t_data;

#endif

