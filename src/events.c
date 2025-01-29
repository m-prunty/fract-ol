/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:43:57 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 11:30:48 by mprunty          ###   ########.fr       */
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
int	move(t_fractal *f, int axis, double delta)
{
	if (axis == 'x')
		f->shift.x += (delta * f->zoom);
	else if (axis == 'y')
		f->shift.y += (delta * f->zoom);
	update_centre(f);
	return (1);
}

/**
 * @brief function to in/decrement f.iterations
 *
 * @param f t_fractal object 
 * @param delta  int amount to inc/dec f.iterations by
 */
int	inc_iters(t_fractal *f, double delta)
{
	f->iters += delta;
	return (1);
}

/**
 * @brief function move the screen
 *
 * @param f fractal object
 * @param axis axis i.e 'x' or 'y'
 * @param delta amount to move by
 * Math.exp(Math.log(130/100) / 20)
 */
int	zoom(t_fractal *f, int dir)
{
	double	factor;

	factor = 1.1;
	if (dir > 0)
	{
		f->zoom /= factor;
		inc_iters(f, 1);
	}
	else if (dir < 0)
	{
		f->zoom *= factor;
		inc_iters(f, -1);
	}
	return (1);
}
