/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:43:57 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 16:13:03 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

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

void	zoom_centre(t_fractal *f)
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
