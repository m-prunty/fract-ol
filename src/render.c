/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:25:59 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 07:28:29 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include <stdio.h>

/*
void	render_sidebar(t_fractal *f)
{
	int		ilen;
	int		hlen;
	int		i;

	i = 0;
	ilen = 0;
	hlen = 0;
	clear_sidebar(f);
	if (f->side.is_visible)
		ilen = sidestr_info(f);
	if (f->show_help)
		hlen = sidestr_help(f);
	while (i < ilen || i < hlen)
	{
		if (f->side.is_visible && i < ilen)
			mlx_string_put(f->mlx_con, f->mlx_win, f->imgsize.x + 10,
				(i * 20) + 10, WHITE, f->info[i]);
		if (f->show_help && i < hlen)
			mlx_string_put(f->mlx_con, f->mlx_win, f->imgsize.x + 10,
				(HEIGHT - hlen * 20) + (i * 20), WHITE, f->help[i]);
		i++;
	}
}
*/
void	render_f(t_fractal *f)
{
	t_complex	pixel;

	if (*f->name == 's')
	{
		if (f->tri)
			clean_tri(f->tri);
		init_serptri(f);
		triangle(f, f->tri);
	}
	else
	{
		pixel.y = 0;
		while (pixel.y < HEIGHT)
		{
			pixel.x = 0;
			while (pixel.x < WIDTH)
			{
				place_pixel(f, &pixel);
				pixel.x++;
			}
			pixel.y++;
		}
	}
	printf("zoom = %f, shift = %f, %f, centre = %f, %f, mouse= %f, %f, iters= %d\n", f->zoom, f->shift.x, f->shift.y, f->centre.x, f->centre.y, f->mouse.pos.x, f->mouse.pos.y, f->iters);
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->img.img, 0, 0);
	return ;
}

void	info_clr_init(t_fractal *f)
{
	int	i;

	if (f->info)
	{
		i = 0;
		while (f->info[i])
		{
			free(f->info[i]);
			f->info[i] = NULL;
		}
	}
	else
	{
		f->info = (char **)malloc(sizeof(char *) * 12);
		if (!f->info)
			return ;
	}
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
