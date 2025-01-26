/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:23:03 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 14:45:56 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	switch_fractal(int keysym, t_fractal *f)
{
	if (keysym == KEY_J)
		*f->name = 'j';
	else if (keysym == KEY_M)
		*f->name = 'm';
	else if (keysym == KEY_S)
		*f->name = 's';
	init_values(f);
	render_f(f);
	return (0);
}

int	mouse_press(int button, int x, int y, t_fractal *f)
{
	if (button == Button1)
	{
		f->mouse.is_pressed = 1;
		f->mouse.pos = (map_complex(&(t_complex){x, y}, f));
	}
	else if (button == Button4)
		zoom(f, 1);
	else if (button == Button5)
		zoom(f, -1);
	if (button == Button4 || button == Button5)
		render_f(f);
	return (0);
}

int	mouse_motion(int x, int y, t_fractal *f)
{
	f->mouse.pos = map_complex(&(t_complex){x, y}, f);
	return (0);
}

int	mouse_release(int button, int x, int y, t_fractal *f)
{
	if (button == Button1)
	{
		f->mouse.is_pressed = 0;
		f->mouse.pos = map_complex(&(t_complex){x, y}, f);
		if (*f->name == 'j')
		{
			f->c = f->mouse.pos;
			render_f(f);
		}
	}
	return (0);
}
