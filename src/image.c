/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mprunty <mprunty@student.42london.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/09 11:37:23 by mprunty		   #+#	#+#			 */
/*   Updated: 2025/01/12 02:20:21 by mprunty          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */
#include "fractol.h"

int linear_interpolation(double t, t_fractal *fractal)
{
    int r, g, b;

	(void)fractal;
    
    // Cycle through colors based on iteration count
    t = t * 6.28318; // 2 * PI
    
    r = (sin(t) + 1) * 127;
    g = (sin(t + 2.0944) + 1) * 127; // 2*PI/3
    b = (sin(t + 4.18879) + 1) * 127; // 4*PI/3
    
    return (r << 16) | (g << 8) | b;
}/*
int	linear_interpolation(double t, t_fractal *fractal)
{
	int	red;
	int	green;
	int	blue;

	(void)fractal;
	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	red = ((WHITE >> 16) & 0xFF) * t;
	green = ((WHITE >> 8) & 0xFF) * t;
	blue = (WHITE & 0xFF) * t;
	return ((red << 16) | (green << 8) | blue);
}
*/
int	normal_color(t_complex z, t_complex der, t_fractal *fractal)
{
	t_complex	u;
	t_complex	v;
	double		t;
	double		angle;

	angle = 2.0 * 1.5 * M_PI / 360.0;
	ft_complex_exp(angle, &v);
	u = ft_complex_divide(z, der);
	u.x /= ft_complex_abs(u);
	u.y /= ft_complex_abs(u);
	t = ft_complex_dot(&u, &v) + 2;
	t = t / (1 + 2);
	return (linear_interpolation(t, fractal));
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
	map.x = (pixel->x / WIDTH * f->minmax.x + f->minmax.y) 
					* f->zoom + f->shift.x;
	map.y = (pixel->y / HEIGHT * 2.0 + 1.0)
					* f->zoom + f->shift.y;
/*	map.x = scale_linear(pixel->x, f->minmax, f->screensize) 
		* f->zoom
		+ f->shift.x;
	map.y = scale_linear(pixel->y, f->minmax, f->screensize)
		* f->zoom
		+ f->shift.y;
	*/
	return (map);
}

void	init_constant(t_fractal *f, t_complex *c, t_complex *z)
{
	if (*f->name != 'j')
	{
		c->x = z->x;
		c->y = z->y;
	}
}

void	place_pixel(t_fractal *f, t_complex *pixel)
{
	t_complex	z;
	t_complex	zprime;
	t_complex	c;
	int			i;
	int			col;

	if (*f->name == 'm' )
	{
		z = (t_complex){0.0, 0.0};
		c = map_complex(pixel, f);
	}
	else
	{
		z = map_complex(pixel, f);
		c = f->c;
	}
	i = 0;
	while (i++ < f->iters)
	{
		if ((z.x * z.x + z.y * z.y) > f->esc)
		{
			// Smooth coloring based on escape iteration
			//double smooth = i + 1 - log(log(z.x * z.x + z.y * z.y)) / log(2);
			col = linear_interpolation(i,f);//smooth / f->iterations, f);
			return my_mlx_pixel_put(&f->img, pixel->x, pixel->y, col);
		}
		zprime.x = z.x * z.x - z.y * z.y + c.x;
		zprime.y = 2 * z.x * z.y + c.y;
		z = zprime;
		i++;
	}
	// Point did not escape - in the set
	my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
}


void	render_chunk(t_fractal *f, int chunk_x, int chunk_y)
{
	t_complex	pixel;

	pixel.y = chunk_y;
	while (pixel.y < fmin(chunk_y + CHUNKS, HEIGHT) )
	{
		pixel.x = chunk_x;
		while (pixel.x < fmin(chunk_x + CHUNKS, WIDTH))
		{
			pixel.x++;
			place_pixel(f, &pixel);
		}
		pixel.y++;
	}
}

/**
 * @brief 
 *
 * @param f 
 */
void	render_f(t_fractal *f)
{
	int 		x;
	int 		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_chunk(f, x, y);
			x += CHUNKS;
		}
		y += CHUNKS;	
	}

	mlx_put_image_to_window(f->mlx_con, f->mlx_win, 
			f->img.img, WIDTH/2, HEIGHT/2);
	return ;
}
/*
void	render_overlay(t_fractal *f)
{
	mlx_put_image_to_window(f->mlx_connection, f->mlx_win, 
			f->img.overlay, WIDTH/2, HEIGHT/2);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_chunk(f, x, y);
			x += CHUNKS;
		}
		y += CHUNKS;	
	}

	mlx_put_image_to_window(f->mlx_connection, f->mlx_win, f->img.img, 0, 0);
	return ;
}
	mlx_string_put(f->mlx_connection, f->mlx_win, 20, 30, 0XFFFFFF - WHITE,
			"Help: h");i


			*/
