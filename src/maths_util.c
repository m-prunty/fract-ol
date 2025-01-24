/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:17:08 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 19:54:35 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

/**
 * @brief y = y1 + ((x-x1) * (y2-y1) / (x2-x1))
 *
 * @param n 
 * @param p1 
 * @param p2 
 * @return 
 */
double	scale_linear(double n, t_complex p1, t_complex p2)
{
	return (p1.y + ((n - p1.x) * (p2.y - p1.y) / (p2.x - p1.x)));
}

double	ft_distsqrd(t_complex a, t_complex b)
{
	return (pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/**
 * @brief (x + yi)^2 = (x^2 - y^2) + 2xyi
 *
 * @param z 
 * @return 
 */
t_complex	ft_complex_sqrd(t_complex z)
{
	t_complex	c;

	c.x = pow(z.x, 2) - pow(z.y, 2);
	c.y = 2 * (z.x) * (z.y);
	return (c);
}

t_complex	ft_complex_sum(t_complex z1, t_complex z2)
{
	t_complex	c;

	c.x = (z1.x) + (z2.x);
	c.y = (z1.y) + (z2.y);
	return (c);
}
