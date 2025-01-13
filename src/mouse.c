#include "fractol.h"

void draw_selection_rectangle(t_fractal *f)
{
	int x;
	int	y;
	int min_x = fmin(f->mouse.start_x, f->mouse.end_x);
	int max_x = fmax(f->mouse.start_x, f->mouse.end_x);
	int min_y = fmin(f->mouse.start_y, f->mouse.end_y);
	int max_y = fmax(f->mouse.start_y, f->mouse.end_y);

	// Draw horizontal lines
	y = min_y;
	while (y <= max_y)
	{
		x = min_x;
		while (x <= max_x)
		{
			if (y == min_y || y == max_y || x == min_x || x == max_x)
				my_mlx_pixel_put(&f->img, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}	
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->img.img, 0, 0);
}

// Mouse button press handler
int mouse_press(int button, int x, int y, t_fractal *f)
{
	if (button == Button1) // Left click
	{
		f->mouse.is_pressed = 1;
		f->mouse.start_x = x;
		f->mouse.start_y = y;
		f->mouse.end_x = x;
		f->mouse.end_y = y;
	}
	else if (button == Button4) // Scroll up
		f->zoom *= 1.05;
	else if (button == Button5) // Scroll down
		f->zoom *= 0.95;
	if (button == Button4 || button == Button5)
		render_f(f);
	return (0);
}

// Mouse motion handler
int mouse_motion(int x, int y, t_fractal *f)
{
	if (f->mouse.is_pressed)
	{
		f->mouse.end_x = x;
		f->mouse.end_y = y;
		// Redraw the fractal and selection rectangle
		//render_f(f);
		draw_selection_rectangle(f);
	}
	return (0);
}

// Mouse button release handler
int mouse_release(int button, int x, int y, t_fractal *f)
{
	if (button == Button1)
	{
		t_complex start_pos, end_pos;
		double width_ratio;//, height_ratio;
		f->mouse.is_pressed = 0;
		f->mouse.end_x = x;
		f->mouse.end_y = y;
		// Convert selection coordinates to complex plane coordinates
		t_complex pixel_start = {f->mouse.start_x, f->mouse.start_y};
		t_complex pixel_end = {f->mouse.end_x, f->mouse.end_y};
		start_pos = map_complex(&pixel_start, f);
		end_pos = map_complex(&pixel_end, f);
		// Calculate new zoom and position
		width_ratio = fabs(end_pos.x - start_pos.x);
		//height_ratio = fabs(end_pos.y - start_pos.y);
		// Update the fractal view
		f->zoom *= 3.5 / width_ratio;
		f->shift.x = -(start_pos.x + end_pos.x) / 2;
		f->shift.y = -(start_pos.y + end_pos.y) / 2;
//		render_f(f);
	}
	return (0);
}

