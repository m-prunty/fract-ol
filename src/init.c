#include "fractol.h"

/**
 * @brief initialise starting fractal
 *
 * @param f 
 * @return 
 */
void	init_f(t_fractal *f)
{
	f->mlx_connection = mlx_init();
	if (!(f->mlx_connection))
		return ((void)error_func(2, "Could not establish mlx_connection"));
	f->mlx_window = mlx_new_window(f->mlx_connection, HEIGHT, WIDTH, f->name);
	if (!(f->mlx_window))
		return (clean_fractal(f, 3,"Could not establish mlx_new_window"));
	f->img.img = mlx_new_image(f->mlx_connection, HEIGHT, WIDTH);
	if (!(f->img.img))
		return (clean_fractal(f, 4, "Could not establish mlx_new_image"));
	f->img.pxl_addr = mlx_get_data_addr(f->img.img,
			&f->img.bits_per_pixel,
			&f->img.line_length,
			&f->img.endian);
	init_events(f);
	return ;
}

/**
 * @brief 
 *
 * @param f 
 */
void	init_events(t_fractal *f){
	mlx_hook(f->mlx_window,
			KeyPress,
			KeyPressMask,
			key_handler,
			f);
	mlx_hook(f->mlx_window,
			ButtonPress,
			ButtonPressMask,
			mouse_handler,
			f);
	mlx_hook(f->mlx_window,
			DestroyNotify,
			StructureNotifyMask,
			close_handler,
			f);
	/*	mlx_hook(f->mlx_window,
		MotionNotify,
		PointerMotionMask,
		julia_track,
		f);
		*/
}

/**
 * @brief 
 *
 * @param f 
 */
void	init_values(t_fractal *f, char **av)
{
	f->zoom = 1.0;
	f->iterations = 50;
	f->escape = 4;
	f->minmax = (t_complex){2, -2};
	f->shift = (t_complex){0.5,1};
	//f->minmax.x, f->minmax.y};
f->screensize = (t_complex){800, 0};
if (*(f->name) == 'j')
{
	f->c.x = ft_atof(*av++);
	f->c.y = ft_atof(*av);
}
else
{
	f->c.x = 0; 
	f->c.y = 0;
}
return ;
}
