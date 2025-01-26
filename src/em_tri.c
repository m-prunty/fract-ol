/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   em_tri.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:30 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 11:52:55 by mprunty          ###   ########.fr       */
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
		my_mlx_pixel_put(f, pixel->x, pixel->y, WHITE);
	}
	else
		my_mlx_pixel_put(f, pixel->x, pixel->y, BLACK);
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
/*
void	subtriangle(t_fractal *f, t_tri *parent_tri, t_tri *t, int current_depth, int max_depth, int colour)
{
	t_complex	pixel;
	int			start;
	int			end;
	t_tri		parent[3];
	t_tri		child[3];

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
			my_mlx_pixel_put(f, pixel.x, pixel.y, colour);
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
		colour = ((int)((colour >> 16) * 0.9) << 16) + ((int)(((colour >> 8) & 0xFF) * 0.9) << 8) + (int)((colour & 0xFF) * 0.9);
		set_exact(&parent[0].a, &parent_tri->a);
		set_exact(&parent[0].b, &t->c);
		set_exact(&parent[0].c, &t->a);
		set_exact(&parent[1].a, &t->c);
		set_exact(&parent[1].b, &parent_tri->b);
		set_exact(&parent[1].c, &t->b);
		set_exact(&parent[2].a, &t->a);
		set_exact(&parent[2].b, &t->b);
		set_exact(&parent[2].c, &parent_tri->c);
		set_midpoint(&child[0].a, &parent_tri->a, &t->a);
		set_midpoint(&child[0].b, &t->a, &t->c);
		set_midpoint(&child[0].c, &parent_tri->a, &t->c);
		set_midpoint(&child[1].a, &t->c, &t->b);
		set_midpoint(&child[1].b, &parent_tri->b, &t->b);
		set_midpoint(&child[1].c, &parent_tri->b, &t->c);
		set_midpoint(&child[2].a, &parent_tri->c, &t->a);
		set_midpoint(&child[2].b, &parent_tri->c, &t->b);
		set_midpoint(&child[2].c, &t->a, &t->b);
		subtriangle(f, &parent[0], &child[0], current_depth + 1, max_depth, colour);
		subtriangle(f, &parent[1], &child[1], current_depth + 1, max_depth, colour);
		subtriangle(f, &parent[2], &child[2], current_depth + 1, max_depth, colour);
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
			my_mlx_pixel_put(f, pixel.x, pixel.y, BLACK);
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
			my_mlx_pixel_put(f, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		while (start <= pixel.x && pixel.x <= end && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(f, pixel.x, pixel.y, 0x444444);
			pixel.x++;
		}
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(f, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	while (pixel.y < f->imgsize.y)
	{
		pixel.x = 0;
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(f, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}

set_midpoint(&child.a, &t->a, &t->c);
set_midpoint(&child.b, &t->b, &t->c);
set_midpoint(&child.c, &t->a, &t->b);
subtriangle(f, t, &child, 1, 7, RED);
}
*/
void draw_line(t_fractal *f, t_complex start, t_complex end, int colour) {
	t_complex pixel = start;
	while (pixel.x <= end.x && pixel.x < f->imgsize.x) {
		my_mlx_pixel_put(f, pixel.x, pixel.y, colour);
		pixel.x++;
	}
}

void fill_triangle_row(t_fractal *f, t_tri *t, t_complex *pixel, int colour) {
	int start = t->c.x - (t->c.x - t->a.x) * (pixel->y - t->c.y) / (t->a.y - t->c.y);
	int end = t->c.x + (t->c.x - t->a.x) * (pixel->y - t->c.y) / (t->a.y - t->c.y);
	pixel->x = start;
	draw_line(f, *pixel, (t_complex){end, pixel->y}, colour);
}

void draw_triangle(t_fractal *f, t_tri *t, int colour) {
	t_complex pixel = {0, t->a.y};
	while (pixel.y <= t->c.y && pixel.y < f->imgsize.y) {
		fill_triangle_row(f, t, &pixel, colour);
		pixel.y++;
	}
}

void set_triangles(t_tri *parent, t_tri *child, t_tri *t, t_tri *parent_tri) {
	set_exact(&parent[0].a, &parent_tri->a);
	set_exact(&parent[0].b, &t->c);
	set_exact(&parent[0].c, &t->a);
	set_exact(&parent[1].a, &t->c);
	set_exact(&parent[1].b, &parent_tri->b);
	set_exact(&parent[1].c, &t->b);
	set_exact(&parent[2].a, &t->a);
	set_exact(&parent[2].b, &t->b);
	set_exact(&parent[2].c, &parent_tri->c);
	set_midpoint(&child[0].a, &parent_tri->a, &t->a);
	set_midpoint(&child[0].b, &t->a, &t->c);
	set_midpoint(&child[0].c, &parent_tri->a, &t->c);
	set_midpoint(&child[1].a, &t->c, &t->b);
	set_midpoint(&child[1].b, &parent_tri->b, &t->b);
	set_midpoint(&child[1].c, &parent_tri->b, &t->c);
	set_midpoint(&child[2].a, &parent_tri->c, &t->a);
	set_midpoint(&child[2].b, &parent_tri->c, &t->b);
	set_midpoint(&child[2].c, &t->a, &t->b);
}

void subtriangle(t_fractal *f, t_tri *p_tri, t_tri *c_tri, int depth) {
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

void triangle(t_fractal *f, t_tri *t) {
	t_complex	pixel;
	t_tri		child;
	
	pixel = (t_complex){0, 0};
	while (pixel.y < f->imgsize.y)
	{
		draw_line(f, pixel, (t_complex){f->imgsize.x, pixel.y}, BLACK);
		pixel.y++;
	}
	draw_triangle(f, t, t->colour);
	child.colour = RED;
	set_midpoint(&child.a, &t->a, &t->c);
	set_midpoint(&child.b, &t->b, &t->c);
	set_midpoint(&child.c, &t->a, &t->b);
	subtriangle(f, t, &child, 1);
}

void	clean_tri(t_tri *t)
{
	if (t->sub1)
		clean_tri(t->sub1);
	if (t->sub2)
		clean_tri(t->sub2);
	if (t->sub3)
		clean_tri(t->sub3);
	free(t);
	return ;
}
t_complex	map_complex_tri(t_complex *pixel, t_fractal *f)
{
	pixel->x = (pixel->x - f->centre.x) * f->zoom + f->centre.x + f->shift.x;
	pixel->y = (pixel->y - f->centre.y) * f->zoom + f->centre.y + f->shift.y;
	return (*pixel);
}


int	init_serptri(t_fractal *f)
{
	f->tri = malloc(sizeof(t_tri));
	if (!f->tri)
		return (0);
	update_centre(f);
	f->tri->a = map_complex_tri(&(t_complex){f->imgsize.x * 0.05, f->imgsize.y * 0.95}, f);
	f->tri->b = map_complex_tri(&(t_complex){f->imgsize.x * 0.95, f->imgsize.y * 0.95}, f);
	f->tri->c = map_complex_tri(&(t_complex){f->imgsize.x * 0.5, f->imgsize.y * 0.05}, f);
	f->tri->sub1 = NULL;	
	f->tri->sub2 = NULL;
	f->tri->sub3 = NULL;
	f->tri->colour = 0x444444;
	set_midpoint(&f->tri->mid_ab, &f->tri->a, &f->tri->b);
	set_midpoint(&f->tri->mid_bc, &f->tri->b, &f->tri->c);
	set_midpoint(&f->tri->mid_ca, &f->tri->c, &f->tri->a);
	f->zoom = 1.0;
	if (f->c.x >= 2)
		f->iters = (int)f->c.x;
	else
		f->iters = 6;
	return (1);
}
