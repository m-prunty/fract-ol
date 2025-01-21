/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:43:57 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/21 01:15:26 by mprunty          ###   ########.fr       */
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
	f->centre = map_complex(&((t_complex){WIDTH / 2, HEIGHT / 2}), f);
	return ;
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
}
void	inc_esc(t_fractal *f, double delta)
{
	f->esc += delta;
}
void zoom_centre(t_fractal *f)
{
	double		d;

	d = sqrt(ft_distsqrd(f->centre, f->mouse.end)) / 2;
	if (f->mouse.end.x < f->centre.x)
		move(f, 'x', -d);
	else
		move(f, 'x', d);
	if (f->mouse.end.y < f->centre.y)
		move(f, 'y', -d);
	else
		move(f, 'y', d);
	return ;
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
	int			x;
	int			y;

	mlx_mouse_get_pos(f->mlx_con, f->mlx_win, &x, &y);
	f->mouse.start = map_complex(&((t_complex){x, y}), f);
	if (dir > 0)
	{
		f->zoom *= 1.10;
		inc_iters(f, -1);
	}
	else if (dir < 0)
	{
		f->zoom *= 0.90;
		inc_iters(f, +1);
	}
	f->mouse.end = map_complex(&((t_complex){x, y}), f);
	zoom_centre(f);
	render_f(f);
}
int	recentre(t_fractal *f)
{
	f->centre = (t_complex){0, 0};
	if (*f->name == 'j') 
		f->shift = (t_complex){1.25, 1.25};
	else if (*f->name == 's')
		f->shift = (t_complex){0, 0};
	else
		f->shift = (t_complex){0.5, 1.25};
	return (1);
}
int	switch_fractal(int keysym, t_fractal *f)
{
	if (keysym == KEY_J)
		*f->name = 'j';
	else if (keysym == KEY_M)
		*f->name = 'm';
	else if (keysym == KEY_S)
		*f->name = 's';
	init_values(f);
	render_f(f);
	return (0);
}
int	char_key_handler(int keysym, t_fractal *f)
{
	if (keysym == KEY_R && init_values(f))
		render_f(f);
	else if (keysym == KEY_H)
		f->show_help = !f->show_help;
	else if (keysym == KEY_O)
		f->side.is_visible = !f->side.is_visible;
	else if (keysym == KEY_C && recentre(f))
		render_f(f);
	else if (keysym == KEY_I)
		inc_esc(f, 1);
	else if (keysym == KEY_K)
		inc_esc(f, -1);
	else if (keysym == KEY_J || keysym == KEY_M || keysym == KEY_S)
		switch_fractal(keysym, f);
	render_sidebar(f);
	return (0);
}
int image_key_handler(int keysym, t_fractal *f)
{
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
	else if (keysym == KEY_SPACE)
		f->colour_shift += 2;
	render_f(f);
	render_sidebar(f);
	return (0);
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
	if (keysym == KEY_ESC)
		close_handler(f);
	if ((keysym >= 97 && keysym <= 122))
		char_key_handler(keysym, f);
	else
		image_key_handler(keysym, f);
	return (0);
}
