#include "../include/fractol.h"

int	is_in_mandelbrot_set(double x, double y)
{
	double	p;
	double	q;

	p = sqrt((x - 0.25) * (x - 0.25) + y * y);
	if (x < p - 2 * p * p + 0.25)
		return (1);
	q = (x + 1) * (x + 1) + y * y;
	if (q <= 1.0 / 16.0)
		return (1);
	return (0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    int    dst;

	dst =  (y * data->line_length) + (x * (data->bits_per_pixel/ 8 ));
	 *(unsigned *)(data->pxl_addr + dst) = color ;
     return ;
}

void    place_pixel(t_fractal f, t_complex pixel)
{
    t_complex   z;
    t_complex   c;
    int color;
    int i;

    z.y = ((scale_linear(pixel.x, f.minmax, f.screensize) * f.zoom) + f.shift.y) ;
    z.x = ((scale_linear(pixel.y, f.minmax, f.screensize) * f.zoom) + f.shift.x) ;
    i = 0;
   	if (is_in_mandelbrot_set(z.x, z.y) && f.name =="m")
    	return (my_mlx_pixel_put(&f.img, pixel.x, pixel.y, BLACK));
    while (i < f.iterations)
    {
        z = ft_complex_sum(ft_complex_sqrd(z), f.c);
        if (pow(z.y, 2) +pow(z.x, 2) > 2*2)
        {
            color = (BLACK + WHITE  * i) / f.iterations;
            my_mlx_pixel_put(&f.img, pixel.x,pixel.y, color);
            return;
        }
        ++i;
    }
    //printf("\nz:%f %f,  c:%f %f", z.y, z.x, c.y, c.x );
    my_mlx_pixel_put(&f.img, pixel.x, pixel.y, LIME_SHOCK);
}

void    render_f(t_fractal *f){
{
	int	x;
	int	y;
    t_complex   pixel;

	pixel.y = -1;
	while (++pixel.y < HEIGHT)
	{
		pixel.x = -1;
		while (++pixel.x < WIDTH)
		{
		    place_pixel(*f, pixel);
		}
	}
	mlx_put_image_to_window(f->mlx_connection,
							f->mlx_window,
							f->img.img,
							0, 0);	

}
    return; }

