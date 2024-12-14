#include "../include/fractol.h"
#include "../include/mlx.h"
#include "X11/X.h"
#include <stdio.h> 
#include <stdlib.h>


/*
 * ESC or i press the x🔴 in the window
 * there won't be leaks!
 * int (*f)(void *param)
*/
int	close_handler(t_fractal *f)
{
	mlx_destroy_image(f->mlx_connection,
					f->img.img);
    clean_fractal(f, -1);
	exit(EXIT_SUCCESS);
}
void    move(t_fractal *f, int axis ,double delta)
{
    if  (axis == 'x')
        f->shift.x += (delta * f->zoom);
    else if  (axis == 'y')
        f->shift.y += (delta * f->zoom);
	render_f(f);
}
void    increment(t_fractal *f, double element, double delta)
{
    f->iterations += delta;
    //element += delta;
    render_f(f);
}

/*
 * Keypress prototype
 * int (*f)(int keycode, void *param)
*/
int	key_handler(int keysym, t_fractal *f)
{
    ft_printf("\t%i\t", keysym);
	if (keysym == KEY_ESC )
		close_handler(f);
	if (keysym == KEY_LEFT)
        move(f, 'x', -0.5);
	else if (keysym == KEY_RIGHT)
        move(f, 'x', 0.5);
	else if (keysym ==KEY_UP)
        move(f, 'y', 0.5);
	else if (keysym == KEY_DOWN)
        move(f, 'y', -0.5);
	else if (keysym == KEY_PLUS)
        increment(f, f->iterations, 10);
	else if (keysym == KEY_MINUS)	
        increment(f, f->iterations, -10);

	return 0;
}



/*
 * int (*f)(int button, int x, int y, void *param)
*/
int	mouse_handler(int button, int x, int y, t_fractal *f)
{
	//Zoom in
	if (button == Button5)
	{
		f->zoom *= 0.95;
	}
	//Zoom out
	else if (button == Button4)
	{
		f->zoom *= 1.05;
	}
	// refresh
    render_f(f);
    (void)x;
    (void)y;
	return 0;
}

/*
 * TRACK the mouse
 * to change julia dynamically
 * int (*f)(int x, int y, void *param)
*/
/*
int	julia_track(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	return 0;
}
*/
