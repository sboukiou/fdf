#ifndef FDF_H
# define FDF_H

#include <stdlib.h>
#include <mlx.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <fcntl.h>

/*Including Dependencies headers*/
# include "dependencies/libft/libft.h"
# include "dependencies/ft_printf/ft_printf.h"

# define TRUE 1
# define FALSE 0
# define FAIL -1
# define ESCAPE 65307
/*Defining Window demensions*/
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
/*Defining Colors*/
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define GREEN 0x00FF00
# define BLUE 0xFF00FF
/*Defining Macros for events*/
# define KEY_PRESS_EVENT 2
# define BTN_PRESS_EVENT 4
# define DESTROY_NOTIFY_EVENT 17
# define KEY_PRESS_MASK 1L<<0
# define BTN_PRESS_MASK 1L<<2
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


typedef struct s_parameters
{
	float	scale;
	int		offset_x;
	int		offset_y;
	int	max_width;
	int	min_width;
	int	max_height;
	int	min_height;
}	t_parameters;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	char	*values;
	int		color;
}	t_point;

typedef struct s_mapinfo
{
	char			***map;
	size_t			height;
	t_parameters	params;
}	t_mapinfo;

typedef struct s_moves
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	zoom_in;
	int	zoom_out;
}	t_moves;

/**
	* s_mlx_session - struct holding addresses
	* of mlx session, window
*/
typedef struct s_mxl_session
{
	void	*mlx;
	void	*mlx_win;
	t_img_data *img;
	t_moves	moves;
	t_mapinfo mapinfo;
}	t_mlx_session;

/*Counter functions*/
size_t	list_len(char **list);
size_t	map_len(char ***map);

/*Math functions*/
int	ft_min(int a, int b);
int	ft_max(int a, int b);
int	ft_ishex(char c);
int	handle_hex_lower(char *str);
int	handle_hex_upper(char *str);
float	triangle_area(t_point a, t_point b, t_point extra);

/*Memory handling functions*/
void	free_list(char **list);
void	free_double_list(char ***list);
void	*ft_realloc(void *old, size_t old_size, size_t new_size);

/*Files reading functions*/
char *read_line(int fd);

/*Mlx costum functions*/
void	mlx_put_to_image(t_img_data *img, int x, int y, int color);
int	handle_key(int key_code, t_mlx_session *mlx_session);

/*Drawing functions*/
void	draw_shape(t_mlx_session *session, t_mapinfo mapinfo);

#endif
