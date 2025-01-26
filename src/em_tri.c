/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   em_tri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:30 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 16:15:17 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	draw_line(t_fractal *f, t_complex start, t_complex end, int colour)
{
	t_complex	pixel;

	pixel = start;
	while (pixel.x <= end.x && pixel.x < f->imgsize.x)
	{
		my_mlx_pixel_put(f, pixel.x, pixel.y, colour);
		pixel.x++;
	}
}

void	fill_triangle_row(t_fractal *f, t_tri *t, t_complex *pixel, int colour)
{
	int	strt;
	int	end;

	strt = t->c.x - (t->c.x - t->a.x) * (pixel->y - t->c.y) / (t->a.y - t->c.y);
	end = t->c.x + (t->c.x - t->a.x) * (pixel->y - t->c.y) / (t->a.y - t->c.y);
	pixel->x = strt;
	draw_line(f, *pixel, (t_complex){end, pixel->y}, colour);
}

void	draw_triangle(t_fractal *f, t_tri *t, int colour)
{
	t_complex	pixel;

	pixel = (t_complex){0, t->a.y};
	while (pixel.y <= t->c.y && pixel.y < f->imgsize.y)
	{
		fill_triangle_row(f, t, &pixel, colour);
		pixel.y++;
	}
}

void	subtriangle(t_fractal *f, t_tri *p_tri, t_tri *c_tri, int depth)
{
	t_tri	parent[3];
	t_tri	child[3];
	int		i;
	int		colour;

	i = 3;
	if (depth >= f->iters)
		return ;
	draw_triangle(f, c_tri, c_tri->colour);
	set_triangles(parent, child, c_tri, p_tri);
	colour = ((int)((c_tri->colour >> 16) * 0.9) << 16)
		+ ((int)(((c_tri->colour >> 8) & 0xFF) * 0.9) << 8)
		+ (int)((c_tri->colour & 0xFF) * 0.9);
	while (--i + 1)
	{
		child[i].colour = colour;
		subtriangle(f, &parent[i], &child[i], depth + 1);
	}
}

void	triangle(t_fractal *f, t_tri *t)
{
	t_complex	pixel;
	t_tri		child;

	pixel = (t_complex){0, 0};
	while (pixel.y < f->imgsize.y)
	{
		draw_line(f, pixel, (t_complex){f->imgsize.x, pixel.y}, BLACK);
		pixel.y++;
	}
	draw_triangle(f, t, t->colour);
	child.colour = RED + f->colour_shift;
	set_midpoint(&child.a, &t->a, &t->c);
	set_midpoint(&child.b, &t->b, &t->c);
	set_midpoint(&child.c, &t->a, &t->b);
	subtriangle(f, t, &child, 1);
}
