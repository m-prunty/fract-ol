/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:22:03 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/24 15:25:24 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	char_key_handler(int keysym, t_fractal *f)
{
	if (keysym == KEY_R && init_values(f))
		render_f(f);
	else if (keysym == KEY_H)
		f->show_help = !f->show_help;
	else if (keysym == KEY_O)
		f->side.is_visible = !f->side.is_visible;
	else if (keysym == KEY_C && recentre(f))
		render_f(f);
	else if (keysym == KEY_J || keysym == KEY_M || keysym == KEY_S)
		switch_fractal(keysym, f);
	return (0);
}

int	image_key_handler(int keysym, t_fractal *f)
{
	if (keysym == KEY_LEFT)
		move(f, 'x', -0.25);
	else if (keysym == KEY_RIGHT)
		move(f, 'x', 0.25);
	else if (keysym == KEY_UP)
		move(f, 'y', -0.25);
	else if (keysym == KEY_DOWN)
		move(f, 'y', 0.25);
	else if (keysym == KEY_PLUS)
		inc_iters(f, 10);
	else if (keysym == KEY_MINUS)
		inc_iters(f, -10);
	else if (keysym == KEY_LT)
		zoom(f, -1);
	else if (keysym == KEY_GT)
		zoom(f, 1);
	else if (keysym == KEY_SPACE)
		f->colour_shift += 2;
	render_f(f);
	return (0);
}

/**
 * @brief handles key inputs
 *
 * @param keysym int representation of key pressed
 * @param f t_fractal
 * @return 0
 */
int	key_handler(int keysym, t_fractal *f)
{
	if (keysym == KEY_ESC)
		close_handler(f);
	if ((keysym >= 97 && keysym <= 122))
		char_key_handler(keysym, f);
	else
		image_key_handler(keysym, f);
	return (0);
}

/**
 * @brief closes out the session, destroy all mlx connections and free mem
 *
 * @param f t_fractal to destroy
 */
int	close_handler(t_fractal *f)
{
	clean_fractal(f, -1, "fractal exited cleanly");
	exit(EXIT_SUCCESS);
}
