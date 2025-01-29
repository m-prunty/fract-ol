/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:32:54 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 11:50:02 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	recentre(t_fractal *f)
{
	if (*f->name == 'j')
		f->shift = (t_complex){1.25, 1.25};
	else if (*f->name == 's')
		f->shift = (t_complex){0, 0};
	else
		f->shift = (t_complex){0.5, 1.25};
	update_centre(f);
	return (1);
}

void	update_centre(t_fractal *f)
{
	if (*f->name == 's')
		f->centre = map_complex_tri(&((t_complex){
					(f->imgsize.x + f->shift.x) / 2,
					(f->imgsize.y + f->shift.y) / 2
				}), f);
	else
		f->centre = map_complex(&((t_complex){
					(f->imgsize.x + f->shift.x) / 2,
					(f->imgsize.y + f->shift.y) / 2
				}), f);
}
