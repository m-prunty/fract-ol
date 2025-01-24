/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   em_tri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:30 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 20:32:53 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/*void	place_pixel_triangle(t_fractal *f, t_complex *pixel)
{
	t_complex	point;

	point = map_complex(pixel, f);
	if (edge_chk(point, f->tri->eab) &&
			edge_chk(point, f->tri->ebc) && edge_chk(point, f->tri->eac))
	{
		my_mlx_pixel_put(&f->img, pixel->x, pixel->y, WHITE);
	}
	else
		my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
}
*/
void	set_exact(t_complex *target, t_complex *src)
{
	target->x = src->x;
	target->y = src->y;
}

void	set_midpoint(t_complex *target, t_complex *a, t_complex *b)
{
	target->x = (a->x + b->x) / 2;
	target->y = (a->y + b->y) / 2;
}

void	subtriangle(t_fractal *f, t_tri *parent_tri, t_tri *t, int current_depth, int max_depth, int color)
{
	t_complex	pixel;
	int			start;
	int			end;
	t_tri		parent_a;
	t_tri		parent_b;
	t_tri		parent_c;
	t_tri		child_a;
	t_tri		child_b;
	t_tri		child_c;

	pixel.y = t->a.y;
	while (pixel.y <= t->c.y && pixel.y < f->imgsize.y)
	{
		start = t->c.x - (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		end = t->c.x + (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		pixel.x = 0;
		while (pixel.x < start && pixel.x < f->imgsize.x)
		{
			pixel.x++;
		}
		while (start <= pixel.x && pixel.x <= end && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, color);
			pixel.x++;
		}
		while (pixel.x < f->imgsize.x)
		{
			pixel.x++;
		}
		pixel.y++;
	}
	if (current_depth < max_depth)
	{
		color = ((int)((color >> 16) * 0.9) << 16) + ((int)(((color >> 8) & 0xFF) * 0.9) << 8) + (int)((color & 0xFF) * 0.9);
		set_exact(&parent_a.a, &parent_tri->a);
		set_exact(&parent_a.b, &t->c);
		set_exact(&parent_a.c, &t->a);
		set_exact(&parent_b.a, &t->c);
		set_exact(&parent_b.b, &parent_tri->b);
		set_exact(&parent_b.c, &t->b);
		set_exact(&parent_c.a, &t->a);
		set_exact(&parent_c.b, &t->b);
		set_exact(&parent_c.c, &parent_tri->c);
		set_midpoint(&child_a.a, &parent_tri->a, &t->a);
		set_midpoint(&child_a.b, &t->a, &t->c);
		set_midpoint(&child_a.c, &parent_tri->a, &t->c);
		set_midpoint(&child_b.a, &t->c, &t->b);
		set_midpoint(&child_b.b, &parent_tri->b, &t->b);
		set_midpoint(&child_b.c, &parent_tri->b, &t->c);
		set_midpoint(&child_c.a, &parent_tri->c, &t->a);
		set_midpoint(&child_c.b, &parent_tri->c, &t->b);
		set_midpoint(&child_c.c, &t->a, &t->b);
		subtriangle(f, &parent_a, &child_a, current_depth + 1, max_depth, color);
		subtriangle(f, &parent_b, &child_b, current_depth + 1, max_depth, color);
		subtriangle(f, &parent_c, &child_c, current_depth + 1, max_depth, color);
	}
}

void	triangle(t_fractal *f, t_tri *t)
{
	t_complex pixel;
	int start;
	int end;
	t_tri child;

	pixel.y = 0;
	while (pixel.y < t->c.y && pixel.y < f->imgsize.y)
	{
		pixel.x = 0;
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	while (pixel.y <= t->a.y && pixel.y < f->imgsize.y)
	{
		start = t->c.x - (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		end = t->c.x + (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		pixel.x = 0;
		while (pixel.x < start && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		while (start <= pixel.x && pixel.x <= end && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, 0x444444);
			pixel.x++;
		}
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	while (pixel.y < f->imgsize.y)
	{
		pixel.x = 0;
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	set_midpoint(&child.a, &t->a, &t->c);
	set_midpoint(&child.b, &t->b, &t->c);
	set_midpoint(&child.c, &t->a, &t->b);
	subtriangle(f, t, &child, 1, 7, RED);
}

int	init_serptri(t_fractal *f)
{
	f->tri = tri_def(f->tri,
			map_complex(&((t_complex){f->imgsize.x * 0.05, f->imgsize.y * 0.95}), f),
			map_complex(&((t_complex){f->imgsize.x * 0.95, f->imgsize.y * 0.95}), f),
			map_complex(&((t_complex){f->imgsize.x * 0.5, f->imgsize.y * 0.05}), f));
	f->zoom = 1.0;
	if (f->c.x > 2)
		f->iters = (int)f->c.x;
	else
		f->iters = 6;
	return (1);
}
