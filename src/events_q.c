/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:16:50 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 11:31:12 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	add_event(t_fractal *f, int keysym, t_complex data)
{
	t_event	*new_event;
	t_event	*current;

	new_event = (t_event *)malloc(sizeof(t_event));
	if (!new_event)
	{
		return ;
	}
	new_event->keysym = keysym;
	new_event->data = data;
	new_event->next = NULL;
	current = f->events;
	if (!current)
		f->events = new_event;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_event;
	}
}

int	event_loop(t_fractal *f)
{
	f->frame_count++;
	if (f->frame_count >= f->debounce_frames)
	{
		if (f->events)
		{
			process_events(f);
			render_f(f);
			f->frame_count = 0;
		}
	}
	return (0);
}

void	process_events(t_fractal *f)
{
	t_event	*current;
	t_event	*tmp;

	current = f->events;
	while (current)
	{
		tmp = current;
		if (current->keysym <= 5)
			mouse_press(current->keysym, current->data.x, current->data.y, f);
		else if (current->keysym >= 97 && current->keysym <= 122)
			char_key_handler(current->keysym, f);
		else
			image_key_handler(current->keysym, f);
		current = current->next;
		free(tmp);
	}
	f->events = NULL;
}

void	clear_events(t_fractal *f)
{
	t_event	*current;
	t_event	*tmp;

	current = f->events;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	f->events = NULL;
}
