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
# define WINDOW_HEIGHT 1920
# define WINDOW_WIDTH 1080

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
	int	color;
}	t_pt;


/*Functions prototypes*/

/*Geometry Funcs*/
float	distance(t_pt a, t_pt b);
float	triangle_area(t_pt a, t_pt b, t_pt c);
t_pt	iso_project(t_pt a);

/*Drawing Funcs*/
int	draw_circle(t_mlx_session *session);
int draw_segement(t_mlx_session *session, t_pt a, t_pt b);
int	draw_shapes(t_mlx_session *session);
int draw_line(t_mlx_session *session, t_pt a, t_pt b);


/*Other functions*/
void	terminate(char *code);
void	*ft_realloc(void *old,size_t old_size, size_t new_size);
char *read_file(char *filename);
char *read_line(int fd);
void	free_list(char **list);
size_t	list_len(char **list);
int	check_map_elements(char ***map);
void	free_double_list(char ***list);
char	***parser(int ac, char **av);
size_t	ft_min(size_t a, size_t b);
size_t	ft_max(size_t a, size_t b);
t_pt	**get_full_map(int ac, char **av);
int	check_values(char *str);
int	check_color(char *str);
#endif

