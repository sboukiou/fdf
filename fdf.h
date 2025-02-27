#ifndef FDF_H
# define FDF_H

# include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/*Including Dependencies headers*/
# include "dependencies/libft/libft.h"
# include "dependencies/ft_printf/ft_printf.h"

/*Defining Macros for events*/
# define ESCAPE 65307
# define KEY_PRESS_EVENT 2
# define KEY_PRESS_MASK 1L<<0

/*Defining Macros for error management*/
# define MLX_INIT "MLX_INIT"
# define MLX_WINDOW "MLX_WINDOW"
# define ERROR -1
# define SUCESS 0

/*Defining Window demensions*/
# define WINDOW_HEIGHT 1000
# define WINDOW_WIDTH 1000

/*Defining Colors*/
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0xFF00FF

/**
	* s_mlx_session - struct holding addresses
	* of mlx session, window
*/
typedef struct s_mxl_session
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx_session;

/**
	* s_pt - struct holding points cordinations
*/
typedef struct s_pt
{
	int	x;
	int	y;
	int	z;
}	t_pt;

/*Functions prototypes*/

/*Geometry Funcs*/
float	distance(t_pt a, t_pt b);

/*Drawing Funcs*/
int	draw_circle(t_mlx_session *session);


#endif

