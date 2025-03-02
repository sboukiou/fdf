#ifndef FDF_H
# define FDF_H

# include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

/*Including Dependencies headers*/
# include "dependencies/libft/libft.h"
# include "dependencies/ft_printf/ft_printf.h"

# define TRUE 1
# define FALSE 0

/*Defining Macros for events*/
# define ESCAPE 65307
# define KEY_PRESS_EVENT 2
# define KEY_PRESS_MASK 1L<<0

/*Defining Macros for error management*/
# define MLX_INIT "MLX_INIT"
# define MLX_WINDOW "MLX_WINDOW"

# define FAIL -1
# define SUCCESS 0

/*Defining Window demensions*/
# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920

/*Defining Colors*/
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0xFF00FF

/**
 * s_img_data - Data about the image
 * to be pushed to the window
 */
typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}				t_img_data;


/**
	* s_mlx_session - struct holding addresses
	* of mlx session, window
*/
typedef struct s_mxl_session
{
	void	*mlx;
	void	*mlx_win;
	t_img_data *img;
}	t_mlx_session;


/**
	* s_pt - struct holding points cordinations
*/
typedef struct s_pt
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	line_len;
}	t_pt;


/*Functions prototypes*/

/*Geometry Funcs*/
int	distance(int x1, int y1, int x2, int y2);
float	triangle_area(t_pt a, t_pt b, t_pt c);
t_pt	iso_project(t_pt a);

/*Drawing Funcs*/
int	draw_square(t_mlx_session *session);
int	draw_circle(t_mlx_session *session);

/*Memory functions*/
void	free_map(t_pt	**map);

/*Mlx spec funcs*/
void	mlx_put_to_image(t_img_data *img, int x, int y, int color);
int	handle_key(int key_code, t_mlx_session *mlx_session);
void	mlx_put_to_image(t_img_data *img, int x, int y, int color);

#endif

