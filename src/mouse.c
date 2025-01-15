/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:42:18 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/15 04:26:05 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	draw_box(t_fractal *f)
{
	t_mouse	box;
	int		x;
	int		y;

	box.start.x = fmin(f->mouse.start.x, f->mouse.end.x);
	box.start.y = fmin(f->mouse.start.y, f->mouse.end.y);
	box.end.x = fmax(f->mouse.start.x, f->mouse.end.x);
	box.end.y = fmax(f->mouse.start.y, f->mouse.end.y);
	y = box.start.y;
	while (y <= box.end.y)
	{
		x = box.start.x;
		while (x <= box.end.x)
		{
			if (y == box.start.y || y == box.end.y
				|| x == box.start.x || x == box.end.x)
				my_mlx_pixel_put(&f->overlay, x, y, 0xFFFFFF);
			x++;
		}
		y++;
		render_overlay(f);
	}
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->overlay.img, 0, 0);
}

int	mouse_press(int button, int x, int y, t_fractal *f)
{
	if (button == Button1)
	{
		f->mouse.is_pressed = 1;
		f->mouse.start.x = x;
		f->mouse.start.y = y;
		f->mouse.end.x = x;
		f->mouse.end.y = y;
	}
	else if (button == Button4)
		f->zoom *= 1.05;
	else if (button == Button5)
		f->zoom *= 0.95;
	if (button == Button4 || button == Button5)
		render_f(f);
	return (0);
}

int	mouse_motion(int x, int y, t_fractal *f)
{
	if (f->mouse.is_pressed)
	{
		f->mouse.end.x = x;
		f->mouse.end.y = y;
		render_f(f);
		draw_box(f);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_fractal *f)
{
	t_complex	start_pos;
	t_complex	end_pos;
	double		ratio;

	if (button == Button1)
	{
		f->mouse.is_pressed = 0;
		f->mouse.end.x = x;
		f->mouse.end.y = y;
		start_pos = map_complex(&((t_complex)
				{f->mouse.start.x,
					f->mouse.start.y}), f);
		end_pos = map_complex(&((t_complex)
				{f->mouse.end.x,
					f->mouse.end.y}), f);
		ratio = fabs(end_pos.x - start_pos.x);
		f->zoom = f->zoom / fmax();
		f->shift.x = (start_pos.x + end_pos.x) / 2;
		f->shift.y = (start_pos.y + end_pos.y) / 2;
		render_f(f);
		render_overlay(f);
	}
	return (0);
}
