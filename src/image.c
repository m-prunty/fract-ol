/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mprunty <mprunty@student.42london.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/09 11:37:23 by mprunty		   #+#	#+#			 */
/*   Updated: 2025/01/18 11:00:13 by mprunty          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */
#include "fractol.h"
#include <math.h>

int	linear_interpolation(double t, t_fractal *fractal)
{
	int	r;
	int	g;
	int	b;

	(void)fractal;
	t = t * 2 * M_PI;
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

	map.x = ((pixel->x / WIDTH) * f->minmax.x + f->minmax.y )
		* f->zoom + f->shift.x;
	map.y = ((pixel->y / HEIGHT) * f->minmax.x + f->minmax.y)
		* f->zoom + f->shift.y;
	return (map);
}

void	place_pixel(t_fractal *f, t_complex *pixel)
{
	t_complex	z;
	t_complex	zprime;
	t_complex	c;
	int			i;

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
		if (*f->name == 'm' && is_mandelbulb(z.x, z.y))
			my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
		else if ((z.x * z.x + z.y * z.y) > f->esc)
			return (my_mlx_pixel_put(&f->img, pixel->x, pixel->y,
						linear_interpolation(smooth(i, z) / f->iters , f)));
		zprime.x = z.x * z.x - z.y * z.y + c.x;
		zprime.y = 2 * z.x * z.y + c.y;
		z = zprime;
		i++;
	}
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
	int	x;
	int	y;

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
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->img.img, 0, 0);
	return ;
}

void	clear_overlay(t_fractal *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&f->overlay, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	overlay_help(t_fractal *f)
{
	int		y;
	int		i;
	char	*help[9];

	y = 0;
	i = 0;
	if (!f->show_help)
		return;
	help[0] = "Controls:";
	help[1] = "ESC - Exit";
	help[2] = "Arrow keys - Move view";
	help[3] = "Mouse wheel - Zoom in/out";
	help[4] = "Left click & drag - Select zoom area";
	help[5] = "+/- - Increase/decrease iterations";
	help[6] = "R - Reset view";
	help[7] = "H - Toggle help";
	help[8] = "O - Toggle overlay";
	while (help[i])
	{
		mlx_string_put(f->mlx_con, f->mlx_win, -100, y, WHITE, help[i]);
		y += 20;
	}
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->overlay.img, 0, 0);
}

void	overlay(t_fractal *f)
{
	t_infostr	info[7];
	char		*str;
	int			i;
	int			space;

	i = 0;
	space = 20;
	str = ft_strjoin(	  "Fractal:     " , f->name);
	info[0] = (t_infostr){str, (t_complex){0, 0}};
	info[1] = (t_infostr){"Iterations:  ", (t_complex){f->iters, 0}};
	info[2] = (t_infostr){"Zoom:        ", (t_complex){f->zoom, 0}};
	info[3] = (t_infostr){"Shift:       ", f->shift};
	info[4] = (t_infostr){"Mouse:       ", f->mouse.start};
	info[5] = (t_infostr){"C value:     ", f->c};
	info[6] = (t_infostr){NULL, (t_complex){0, 0}};
	if (f->overlay.is_visible)
	{
		while (info[i].str)
		{
			mlx_string_put(f->mlx_con, f->mlx_win, 20, (i + 1) * space, WHITE,
				str_parsed(info[i]));
			i++;
		}
	}
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->overlay.img, 0, 0);
}

char	*ft_dtostr(double n, int precision)
{
	char	*str;
	int		len;
	int		i;
	char	*frac;
	char	*intg;

	i = (int)(n);
	frac = ft_itoa(fabs(n - i) * (precision * 10));
	intg = ft_itoa((int)(n));
	len = ft_strlen(intg) + precision + 2;
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, intg, len);
	if (ft_strncmp(frac, "0", len))
	{
		ft_strlcat(str, ".", len);
		ft_strlcat(str, frac, len);
	}
	free(frac);
	free(intg);
	return (str);
}

char	*str_parsed(t_infostr info)
{
	char	*res;
	char	*x;
	char	*y;
	int		len;

	len = ft_strlen(info.str);
	x = ft_dtostr(info.c.x, 2);
	y = ft_dtostr(info.c.y, 2);
	len += ft_strlen(x) + ft_strlen(y) + 2;
	res = (char *)malloc(sizeof(char *) * len);
	ft_strlcpy(res, info.str, ft_strlen(info.str) + 1);
	if (info.c.x != 0)
	{
		ft_strlcat(res, x, len);
		if (info.c.y != 0)
		{
			ft_strlcat(res, " ", len);
			ft_strlcat(res, y, len);
		}
	}
	return (res);
}

void	render_overlay(t_fractal *f)
{
	clear_overlay(f);
	if (f->overlay.is_visible)
		overlay(f);
	if (f->show_help)
		overlay_help(f);
}
