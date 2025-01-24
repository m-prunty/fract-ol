/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:23:46 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 18:49:03 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	linear_interpolation(double t, t_fractal *f)
{
	int	r;
	int	g;
	int	b;

	t = t * 2 * M_PI + f->colour_shift;
	r = (sin(t) + 1) * 127;
	g = (sin(t + 2 * FT_PI_3) + 1) * 127;
	b = (sin(t + 4 * FT_PI_3) + 1) * 127;
	return ((r << 16) | (g << 8) | b);
}

double	smooth(int i, t_complex z)
{
	return (i + 1 - log(log(z.x * z.x + z.y * z.y)) / log(2));
}

int	is_mandelbulb(double x, double y)
{
	double	p;
	double	q;

	p = sqrt((x - 0.25) * (x - 0.25) + y * y);
	if (x < p - 2 * p * p + 0.25)
		return (1);
	q = (x + 1) * (x + 1) + y * y;
	if (q <= 1.0 / 16.0)
		return (1);
	return (0);
}
