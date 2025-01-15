#include "fractol.h"

/**
 * @brief initialise starting fractal
 *
 * @param f 
 * @return 
 */
void	init_f(t_fractal *f)
{
	f->mlx_con = mlx_init();
	if (!(f->mlx_con))
		return ((void)error_func(2, "Could not establish mlx_connection"));
	f->mlx_win = mlx_new_window(f->mlx_con, HEIGHT, WIDTH, f->name);
	if (!(f->mlx_win))
		return (clean_fractal(f, 3,"Could not establish mlx_new_window"));
	f->img.img = mlx_new_image(f->mlx_con, HEIGHT, WIDTH);
	if (!(f->img.img))
		return (clean_fractal(f, 4, "Could not establish mlx_new_image"));
	f->img.pxl_addr = mlx_get_data_addr(f->img.img,	&f->img.bits_per_pixel,
			&f->img.line_length, &f->img.endian);
	init_overlay(f);
	init_events(f);
	return ;
}
void	init_overlay(t_fractal *f)
{
	f->overlay.img = mlx_new_image(f->mlx_con, WIDTH, HEIGHT);
	if (!f->overlay.img)
		clean_fractal(f, 4, "Could not create overlay image");
	f->overlay.pxl_addr = mlx_get_data_addr(f->overlay.img,
			&f->overlay.bits_per_pixel,
			&f->overlay.line_length,
			&f->overlay.endian);
	f->overlay.is_visible = 0;
	f->show_help = 0;
}

/**
 * @brief inits all the possible event hooks and defines the functions to be 
 * called when the event is triggered
 *
 * @param f 
 */
void	init_events(t_fractal *f)
{
	mlx_hook(f->mlx_win, ButtonPress, ButtonPressMask, mouse_press, f);
	mlx_hook(f->mlx_win, ButtonRelease, ButtonReleaseMask, mouse_release, f);
	mlx_hook(f->mlx_win, MotionNotify, PointerMotionMask, mouse_motion, f);
	mlx_hook(f->mlx_win, KeyPress, KeyPressMask, key_handler, f);
	mlx_hook(f->mlx_win, DestroyNotify, StructureNotifyMask, close_handler, f);
	/*	mlx_hook(f->mlx_win, MotionNotify, PointerMotionMask, julia_track, f);
	*/
}

/**
 * @brief initialise the starting values for the fractal
 *
 * @param f 
 */
void	init_values(t_fractal *f)
{
	f->zoom = 1.0;
	f->iters = 50;
	f->esc = 4;
	f->minmax = (t_complex){2.5, -2.5};
	f->shift = (t_complex){0.5, 1.25};
	f->scrsize = (t_complex){WIDTH, HEIGHT};
	f->mouse.is_pressed = 0;
	f->mouse.start.x = 0;
	f->mouse.start.y = 0;
	f->mouse.end.x = 0;
	f->mouse.end.y = 0;
}
