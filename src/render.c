/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:25:59 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 22:35:04 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	render_chunk(t_fractal *f, int chunk_x, int chunk_y)
{
	t_complex	pixel;

	pixel.y = chunk_y;
	while (pixel.y < fmin(chunk_y + CHUNKS, HEIGHT))
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

void	render_f(t_fractal *f)
{
	int	x;
	int	y;

	if (*f->name == 's')
	{
		init_serptri(f);
		triangle(f, f->tri);
	}
	else
	{
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
	}
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->img.img, 0, 0);
	render_sidebar(f);
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
