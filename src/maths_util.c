/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 03:17:08 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/15 03:52:57 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/fractol.h"

double	ft_min(double x, double y)
{
	if (x > y)
		return (y);
	return (x);
}
double	ft_max(double x, double y)
{
	if (x < y)
		return (y);
	return (x);
}
double	ft_pow(double d, int pow)
{
	if (pow > 0)
		return (d * ft_pow(d, --pow));
	if (pow < 0)
		return (1 / d * (ft_pow(d, ++pow)));
	return (1);
}
double	ft_sqrtbs(double n)
{
	double	lo;
	double	hi;
	double	mid;
	int		i;

	i = 0;
	lo = ft_min(1, n);
	hi = ft_max(1, n);
	mid = (lo + hi) / 2;
	while (100 * lo * lo < n)
		lo *= 10;
	while (0.01 * hi * hi > n)
		hi *= 0.1;
	while (i < 100)
	{
		mid = (lo + hi) / 2;
		if (mid * mid == n)
			return (mid);
		if (mid * mid > n)
			hi = mid;
		else
			lo = mid;
	}
	return (mid);
}

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

/**
 * @brief (x + yi)^2 = (x^2 - y^2) + 2xyi
 *
 * @param z 
 * @return 
 */
t_complex	ft_complex_sqrd(t_complex z)
{
	t_complex	c;

	c.x = ft_pow(z.x, 2) - ft_pow(z.y, 2);
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
