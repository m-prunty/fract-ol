/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:21:43 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 20:01:44 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	f->mlx_win = mlx_new_window(f->mlx_con, f->wsize.x, f->wsize.y, f->name);
	if (!(f->mlx_win))
		return (clean_fractal(f, 3, "Could not establish mlx_new_window"));
	f->img.img = mlx_new_image(f->mlx_con, f->imgsize.x, f->imgsize.y);
	if (!(f->img.img))
		return (clean_fractal(f, 4, "Could not establish mlx_new_image"));
	f->img.pxl_addr = mlx_get_data_addr(f->img.img, &f->img.bits_per_pixel,
			&f->img.line_length, &f->img.endian);
	init_sidebar(f);
	init_events(f);
	return ;
}

void	init_sidebar(t_fractal *f)
{
	f->side.img = mlx_new_image(f->mlx_con, f->sidesize.x, HEIGHT);
	if (!f->side.img)
		clean_fractal(f, 4, "Could not create sidebar image");
	f->side.pxl_addr = mlx_get_data_addr(f->side.img,
			&f->side.bits_per_pixel,
			&f->side.line_length,
			&f->side.endian);
	f->side.is_visible = 1;
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
}

/**
 * @brief initialise the starting values for the fractal
 *
 * @param f 
 */
int	init_values(t_fractal *f)
{
	f->zoom = 1.0;
	f->iters = 15;
	f->esc = 4;
	f->colour_shift = 1;
	f->minmax = (t_complex){2.5, -2.5};
	f->imgsize = (t_complex){WIDTH, HEIGHT};
	f->sidesize = (t_complex){SWIDTH, HEIGHT};
	f->wsize = (t_complex){WIDTH + SWIDTH, HEIGHT};
	f->mouse.is_pressed = 0;
	f->mouse.start = (t_complex){0, 0};
	f->mouse.end = (t_complex){0, 0};
	recentre(f);
	return (1);
}
