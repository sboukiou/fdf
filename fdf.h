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

# define ESCAPE 65307

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

#define SCALE 30
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


/*Memory functions*/
void	free_double_list(char ***list);
void	free_list(char **list);
void	*ft_realloc(void *old, size_t old_size, size_t new_size);


/*Geometry Funcs*/
int	distance(int x1, int y1, int x2, int y2);
float	triangle_area(t_pt a, t_pt b, t_pt c);
int	ft_min(int a, int b);
int	ft_max(int a, int b);

/*Drawing Funcs*/
int	draw_square(t_mlx_session *session);
void draw_line(t_mlx_session *session, int x0, int y0, int x1, int y1);
int	draw_circle(t_mlx_session *session);
int	draw_map_cordinates(t_mlx_session *session, char ***map);
/*Memory functions*/
void	free_map(t_pt	**map);
void	free_list(char **list);
void	*ft_realloc(void *old, size_t old_size, size_t new_size);
void	free_double_list(char ***list);

/*Mlx spec funcs*/
void	mlx_put_to_image(t_img_data *img, int x, int y, int color);
int	handle_key(int key_code, t_mlx_session *mlx_session);
void	mlx_put_to_image(t_img_data *img, int x, int y, int color);
int		quit_mlx_session(t_mlx_session *session);

/*Parser functions*/
char	***parser(int ac, char **av);

#endif

