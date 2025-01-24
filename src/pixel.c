/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:25:39 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 19:59:06 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	dst;

	dst = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	*(unsigned *)(data->pxl_addr + dst) = color;
	return ;
}

t_complex	map_complex(t_complex *pixel, t_fractal *f)
{
	t_complex	map;

	map.x = ((pixel->x / WIDTH) * f->minmax.x + f->minmax.y)
		* f->zoom + f->shift.x;
	map.y = ((pixel->y / HEIGHT) * f->minmax.x + f->minmax.y)
		* f->zoom + f->shift.y;
	return (map);
}

void	def_z_c(t_fractal *f, t_complex *pixel, t_complex *z, t_complex *c)
{
	if (*f->name == 'm' )
	{
		*z = (t_complex){0.0, 0.0};
		*c = map_complex(pixel, f);
	}
	else
	{
		*z = map_complex(pixel, f);
		*c = f->c;
	}
	return ;
}

void	place_pixel(t_fractal *f, t_complex *pixel)
{
	t_complex	z;
	t_complex	zprime;
	t_complex	c;
	int			i;

	i = 0;
	def_z_c(f, pixel, &z, &c);
	while (i++ < f->iters)
	{
		if (*f->name == 'm' && is_mandelbulb(z.x, z.y))
			my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
		else if ((z.x * z.x + z.y * z.y) > f->esc)
			return (my_mlx_pixel_put(&f->img, pixel->x, pixel->y,
					linear_interpolation(smooth(i, z) / f->iters, f)));
		zprime.x = z.x * z.x - z.y * z.y + c.x;
		zprime.y = 2 * z.x * z.y + c.y;
		z = zprime;
		i++;
	}
	my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
}
