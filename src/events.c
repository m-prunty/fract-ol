/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:43:57 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 14:35:40 by mprunty          ###   ########.fr       */
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
	update_centre(f);
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

	d = ft_distsqrd(f->centre, f->mouse.end) / 2;
	if (f->mouse.pos.x < f->centre.x)
		move(f, 'x', -d);
	else
		move(f, 'x', d);
	if (f->mouse.pos.y < f->centre.y)
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
 * Math.exp(Math.log(130/100) / 20)
 */
void	zoom(t_fractal *f, int dir)
{
	int			x;
	int			y;

	mlx_mouse_get_pos(f->mlx_con, f->mlx_win, &x, &y);
	f->mouse.pos = map_complex(&((t_complex){x, y}), f);
	if (dir > 0)
	{
		f->zoom *= 2 * exp(log(130 / 100) / 20);
		inc_iters(f, -1);
	}
	else if (dir < 0)
	{
		f->zoom /= 2 * exp(log(130 / 100) / 20);
		inc_iters(f, +1);
	}
	zoom_centre(f);
	render_f(f);
}
