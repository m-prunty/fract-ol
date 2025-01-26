/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:25:39 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 08:38:14 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
/*
void	pre_calc(t_fractal *f ,t_data data)
{
	int	x;
	int	y;	

	y = 0;
	while (y < f->imgsize.y)
	{
		data.line_length[y] = data.line_length[y] * y;
		y++;
		while (x < f->imgsize.x)
		{
			data.bits_per_pixel[x] = data.bits_per_pixel[x] / 8;
			x++;
		}
	}
}*/
	/*
	f->offset = (double**)malloc(sizeof(double*) * f->imgsize.y);
	if (!f->offset)
		return ((void)error_func(1, "Could not allocate memory for offset"));
	y = 0;
	while (y < f->imgsize.y)
	{
		// INFO: Allocate memory for each row
		f->offset[y] = (double*)malloc(sizeof(double) * (int)f->imgsize.x);
		if (!f->offset[y])
			return ((void)error_func(1, "Could not allocate memory for offset"));
		++y;

		x = 0;
		while (x < (int)f->imgsize.x)
		{
			//ft_bzero(&f->offset[y][x], sizeof(double));

			printf("> A\n");
			f->offset[y][x] = 1;// (y * f->img.line_length) 
			printf("> B\n");
			//+ (x * f->img.bits_per_pixel / 8);
			++x;
		}
	}
	*/

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

	dst = f->offset[y * (int)f->imgsize.x + x];
	*(unsigned *)(f->img.pxl_addr + dst) = color;
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
