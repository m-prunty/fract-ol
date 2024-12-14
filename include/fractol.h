#ifndef FRACTOL_H
# define FRACTOL_H

#include "mlx.h"
#include "math.h"
#include "libft.h"
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
//#include <keysymdef.h>

typedef struct	s_data {
	void	*img;
	char	*pxl_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex{
    double  x;
    double  y;
}   t_complex;

typedef struct	s_fractal
{
	char	*name;
	//MLX
	void	*mlx_connection; // mlx_init()
	void	*mlx_window; 	 // mlx_new_window()
	//Image
	t_data	img;
    double  zoom;
    int     iterations;
    int     escape;
    t_complex   c;
    t_complex   shift;
    t_complex   minmax;
    t_complex   screensize;
    //
} t_fractal;

#define HEIGHT 800 
#define WIDTH 800 

/*
 * COLORS
*/
#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)

// Psychedelic colors
#define MAGENTA_BURST   0xFF00FF  // A vibrant magenta
#define LIME_SHOCK      0xCCFF00  // A blinding lime
#define NEON_ORANGE     0xFF6600  // A blazing neon orange
#define PSYCHEDELIC_PURPLE 0x660066  // A deep purple
#define AQUA_DREAM      0x33CCCC  // A bright turquoise
#define HOT_PINK        0xFF66B2  // As the name suggests!
#define ELECTRIC_BLUE   0x0066FF  // A radiant blue
#define LAVA_RED        0xFF3300  // A bright, molten red

// Keymap
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_PLUS 61 
# define KEY_MINUS 45 


int     error_code(int i);
int	    create_trgb(int t, int r, int g, int b);
int     draw_line(void *mlx,  int beginX, int beginY, int endX, int endY, int color);
int     clean_fractal(t_fractal *f, int n_error);
double	ft_atof(const char *nptr);

// init
int     init_f(t_fractal *f);
void    init_events(t_fractal *f);
void    init_data(t_fractal *f);

// Image
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    place_pixel(t_fractal f, t_complex pixel);
void    render_f(t_fractal *f);

// maths
double  ft_min(double x, double y);
double  ft_max(double x, double y);
double  ft_pow(double d, int pow);
double  ft_sqrtbs(double n);
double  scale_linear(double n, t_complex new_minmax, t_complex old_minmax);
t_complex   ft_complex_sqrd(t_complex z);
t_complex   ft_complex_sum(t_complex z1, t_complex z2);

// events
int	close_handler(t_fractal *fractal);
int	key_handler(int keysym, t_fractal *fractal);
int	mouse_handler(int button, int x, int y, t_fractal *fractal);
int	julia_track(int x, int y, t_fractal *fractal);


#endif
