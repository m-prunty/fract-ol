/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:06:35 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 15:09:26 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/**
 * @brief cleans up the fractal: destroys mlx, frees mem, and relays any error
 * 
 * @param f main t_fractal object
 * @param n_error error number set to -1 if no error 
 * @param info further info on error, leave blank if none
 */
void	clean_fractal(t_fractal *f, int n_error, char *info)
{
	int	i;

	i = 12;
	if (n_error >= 0)
		error_func(n_error, info);
	if ((f->mlx_win))
		mlx_destroy_window(f->mlx_con, f->mlx_win);
	if ((f->img.img))
		mlx_destroy_image(f->mlx_con, f->img.img);
	if ((f->side.img))
		mlx_destroy_image(f->mlx_con, f->side.img);
	if (f->mlx_con)
		mlx_destroy_display(f->mlx_con);
	if (f->info)
		while (f->info[i])
			free(f->info[i]);
	if (f->tri)
		clean_tri(f->tri);
	free(f->offset);
	free(f->mlx_con);
	if (f->events)
		clear_events(f);
	return ;
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
