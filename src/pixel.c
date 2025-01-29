/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:25:39 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 12:10:45 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	pre_calc(t_fractal *f, t_data *data)
{
	int	x;
	int	y;

	f->offset = malloc(sizeof(int) * f->imgsize.y * f->imgsize.x);
	y = 0;
	while (y < f->imgsize.y)
	{
		x = 0;
		while (x < f->imgsize.x)
		{
			*f->offset = data->line_length * y + x * (data->bits_per_pixel / 8);
			x++;
			f->offset++;
		}
		y++;
	}
	f->offset -= (int)(f->imgsize.y * f->imgsize.x);
}

void	my_mlx_pixel_put(t_fractal *f, int x, int y, int color)
{
	int	dst;

	if (x < 0 || y < 0)
	{
		error_func(1, "pixel put out of bounds!");
		return ;
	}
	dst = f->offset[y * (int)f->imgsize.x + x];
	*(unsigned *)(f->img.pxl_addr + dst) = color;
	return ;
}

t_complex	map_complex(t_complex *pixel, t_fractal *f)
{
	t_complex	map;

	map.x = ((pixel->x / WIDTH) * f->range.x + f->range.y)
		* f->zoom + f->shift.x;
	map.y = ((pixel->y / HEIGHT) * f->range.x + f->range.y)
		* f->zoom + f->shift.y;
	return (map);
}

t_complex	map_complex_tri(t_complex *pixel, t_fractal *f)
{
	pixel->x = (pixel->x - f->centre.x) + f->centre.x + f->shift.x;
	pixel->y = (pixel->y - f->centre.y) + f->centre.y + f->shift.y;
	return (*pixel);
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
			my_mlx_pixel_put(f, pixel->x, pixel->y, BLACK);
		else if ((z.x * z.x + z.y * z.y) > f->esc)
			return (my_mlx_pixel_put(f, pixel->x, pixel->y,
					linear_interpolation(smooth(i, z) / f->iters, f)));
		zprime.x = z.x * z.x - z.y * z.y + c.x;
		zprime.y = 2 * z.x * z.y + c.y;
		z = zprime;
		i++;
	}
	my_mlx_pixel_put(f, pixel->x, pixel->y, BLACK);
}
