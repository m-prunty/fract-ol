/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:23:03 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 12:14:03 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

t_complex	mouse_translate(t_fractal *f, int x, int y)
{
	mlx_mouse_get_pos(f->mlx_con, f->mlx_win, &x, &y);
	f->mouse.pos = (t_complex){x, y};
	f->mouse.trans = map_complex(&f->mouse.pos, f);
	return (f->mouse.trans);
}

void	mouse_zoom(t_fractal *f, int dir)
{
	t_complex	mouse_pre;
	t_complex	mouse_post;

	mouse_translate(f, f->mouse.pos.x, f->mouse.pos.y);
	mouse_pre = f->mouse.trans;
	zoom(f, dir);
	mouse_post = map_complex(&f->mouse.pos, f);
	f->shift.x += (mouse_pre.x) -(mouse_post.x);
	f->shift.y += (mouse_pre.y) - (mouse_post.y);
	update_centre(f);
	return ;
}

int	mouse_handler(int button, int x, int y, t_fractal *f)
{
	t_complex	pos;

	pos = (t_complex){x, y};
	add_event(f, button, pos);
	return (0);
}

int	mouse_press(int button, int x, int y, t_fractal *f)
{
	mouse_translate(f, x, y);
	if (*f->name == 'j' && button == Button1)
	{
		f->c = f->mouse.trans;
		return (1);
	}
	if (button == Button1 || button == Button4)
		mouse_zoom(f, 1);
	else if (button == Button3 || button == Button5)
		mouse_zoom(f, -1);
	return (0);
}

int	mouse_motion(int x, int y, t_fractal *f)
{
	f->mouse.pos = (t_complex){x, y};
	printf("mouse.pos: %f, %f mouse.trans: %f, %f\n",f->mouse.pos.x, f->mouse.pos.y, f->mouse.trans.x, f->mouse.trans.y);
	return (0);
}
