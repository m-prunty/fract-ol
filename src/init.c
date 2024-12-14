#include "../include/fractol.h"
#include "fractol.h"

int init_f(t_fractal *f)
{
    f->mlx_connection = mlx_init();
    if (!(f->mlx_connection))
        return (error_code(2));
    f->mlx_window = mlx_new_window(f->mlx_connection, HEIGHT, WIDTH, f->name);
    if (!(f->mlx_window))
        return clean_fractal(f, 3);
    f->img.img = mlx_new_image(f->mlx_connection,  HEIGHT, WIDTH);
    if (!(f->img.img))
        return clean_fractal(f, 4);
    f->img.pxl_addr = mlx_get_data_addr(f->img.img,
            &f->img.bits_per_pixel,
            &f->img.line_length,
            &f->img.endian);

    init_events(f);
    init_data(f);
    return (1);

}
void    init_events(t_fractal *f){
    mlx_hook(f->mlx_window,
			KeyPress,
			KeyPressMask,
			key_handler,
			f);
	mlx_hook(f->mlx_window,
			ButtonPress,
			ButtonPressMask,
			mouse_handler,
			f);
	mlx_hook(f->mlx_window,
			DestroyNotify,
			StructureNotifyMask,
			close_handler,
			f);
/*	mlx_hook(f->mlx_window,
			MotionNotify,
			PointerMotionMask,
			julia_track,
			f);
*/
}
void    init_data(t_fractal *f){
	f->zoom = 1;
	f->shift.x = 0;
	f->shift.y = 0;
	f->iterations = 42;
	f->escape = 4;
    f->minmax.x = 2;
    f->minmax.y = -2;
    f->screensize.x = 800;
    f->screensize.y = 0;
    return ;
}
