/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:42:18 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/18 11:05:54 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	mouse_press(int button, int x, int y, t_fractal *f)
{
	if (button == Button1)
	{
		f->mouse.is_pressed = 1;
		f->mouse.start = (map_complex(&(t_complex){x, y}, f));
	}
	else if (button == Button4)
		zoom(f, 1);
	else if (button == Button5)
		zoom(f, -1);
	if (button == Button4 || button == Button5)
		render_f(f);
	render_overlay(f);
	return (0);
}

int	mouse_motion(int x, int y, t_fractal *f)
{
	mlx_mouse_get_pos(f->mlx_con, f->mlx_win,
		(int *)&f->mouse.start.x, (int *)&f->mouse.start.y);
	if (f->mouse.is_pressed)
		f->mouse.end = map_complex(&(t_complex){x, y}, f);
//	render_overlay(f);
	return (0);
}

int	mouse_release(int button, int x, int y, t_fractal *f)
{
	//t_complex	start_pos;
	//t_complex	end_pos;
	//double		ratio;
	if (button == Button1)
	{
		f->mouse.is_pressed = 0;
		f->mouse.end = map_complex(&(t_complex){x, y}, f);
	//	start_pos = map_complex(&(
	//				(t_complex){f->mouse.start.x, f->mouse.start.y}), f);
	//	end_pos = map_complex(&(
	//				(t_complex){f->mouse.end.x, f->mouse.end.y}), f);
	//	ratio = fabs(end_pos.x - start_pos.x);
	//	f->zoom = f->zoom / ratio;
	//	f->shift.x = (start_pos.x + end_pos.x) / 2;
	//	f->shift.y = (start_pos.y + end_pos.y) / 2;
	}
//	render_overlay(f);
	return (0);
}
