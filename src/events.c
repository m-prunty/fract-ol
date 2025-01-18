/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:43:57 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/18 11:13:17 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/**
 * @brief closes out the session, destroy all mlx connections and free mem
 *
 * @param f t_fractal to destroy
 */
int	close_handler(t_fractal *f)
{
	clean_fractal(f, -1, "fractal exited cleanly");
	exit(EXIT_SUCCESS);
}

/**
 * @brief function move the screen
 *
 * @param f fractal object
 * @param axis axis i.e 'x' or 'y'
 * @param delta amount to move by
 */
void	move(t_fractal *f, int axis, double delta)
{
	if (axis == 'x')
		f->shift.x += (delta * f->zoom);
	else if (axis == 'y')
		f->shift.y += (delta * f->zoom);
	render_f(f);
}

/**
 * @brief function to in/decrement f.iterations
 *
 * @param f t_fractal object 
 * @param delta  int amount to inc/dec f.iterations by
 */
void	inc_iters(t_fractal *f, double delta)
{
	f->iters += delta;
	render_f(f);
}

/**
 * @brief function move the screen
 *
 * @param f fractal object
 * @param axis axis i.e 'x' or 'y'
 * @param delta amount to move by
 */
void	zoom(t_fractal *f, int dir)
{
	t_complex	prezoom;
	t_complex	postzoom;

	mlx_mouse_get_pos(f->mlx_con, f->mlx_win,
			(int *)&prezoom.x, (int *)&prezoom.y);
	f->mouse.start = map_complex(&prezoom, f);
	prezoom = f->mouse.start;
	printf("\n%f %f", prezoom.x, prezoom.y );
	if (dir > 0)
	{
		f->zoom *= 1.05;
		inc_iters(f, -1);
	}
	else if (dir < 0)
	{
		f->zoom *= 0.95;
		inc_iters(f, +1);
	}
	postzoom = map_complex(&f->mouse.start, f);
	move(f, 'x', (prezoom.x - postzoom.x) );
	move(f, 'y', (prezoom.y - postzoom.y) );
	//f->shift.x += (prezoom.x - postzoom.x) * f->zoom;
	//f->shift.y += (prezoom.y - postzoom.y) * f->zoom;
	render_f(f);
}
/**
 * @brief handles key inputs
 *
 * @param keysym int representation of key pressed
 * @param f t_fractal
 * @return 0
 */
int	key_handler(int keysym, t_fractal *f)
{
	printf("key: %d\n", keysym);
	if (keysym == KEY_ESC)
		close_handler(f);
	if (keysym == KEY_LEFT)
		move(f, 'x', -0.25);
	else if (keysym == KEY_RIGHT)
		move(f, 'x', 0.25);
	else if (keysym == KEY_UP)
		move(f, 'y', -0.25);
	else if (keysym == KEY_DOWN)
		move(f, 'y', 0.25);
	else if (keysym == KEY_PLUS)
		inc_iters(f, 10);
	else if (keysym == KEY_MINUS)
		inc_iters(f, -10);
	else if (keysym == KEY_LT)
		zoom(f, -1);
	else if (keysym == KEY_GT)
		zoom(f, 1);
	else if (keysym == KEY_R)
		init_values(f);
	else if (keysym == KEY_H)
		f->show_help = !f->show_help;
	else if (keysym == KEY_O)
		f->overlay.is_visible = !f->overlay.is_visible;
	render_overlay(f);
	return (0);
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
   fractal->julia_x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) +
   fractal->shift_x; fractal->julia_y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom)
   + fractal->shift_y; fractal_render(fractal);
   }
   return 0;
   }
   */
