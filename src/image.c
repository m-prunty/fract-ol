#include "../include/fractol.h"

int linear_interpolation(double t, t_fractal *fractal)
{
	int red;
	int green;
	int blue;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	red = ((WHITE >> 16) & 0xFF) * t;
	green = ((WHITE >> 8) & 0xFF) * t;
	blue = (WHITE & 0xFF) * t;
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @brief Fonction pour déterminer la couleur d'un pixel à l'extérieur
 *	de l'ensemble de Mandelbrot.
 *
 * @param z Le point z après l'itération finale.
 * @param der La dérivée de z après l'itération finale.
 * @return int Couleur à appliquer au format 0x00RRGGBB.
 */
int normal_color(t_complex z, t_complex der, t_fractal *fractal)
{
	t_complex u;
	t_complex v;
	double t;
	double angle;

	angle = 2.0 * 1.5 * M_PI / 360.0;
	ft_complex_exp(angle, &v);
	u = ft_complex_divide(z, der);
	u.x /= ft_complex_abs(u);
	u.y /= ft_complex_abs(u);
	t = ft_complex_dot(&u, &v) + 2; // + fractal->color_h;
	t = t / (1 + 2);                // fractal->color_h);
	return (linear_interpolation(t, fractal));
}

int is_in_mandelbrot_set(double x, double y)
{
	double p;
	double q;

	p = sqrt((x - 0.25) * (x - 0.25) + y * y);
	if (x < p - 2 * p * p + 0.25)
		return (1);
	q = (x + 1) * (x + 1) + y * y;
	if (q <= 1.0 / 16.0)
		return (1);
	return (0);
}
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int dst;

	//printf("%f", data);
	dst = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	*(unsigned *)(data->pxl_addr + dst) = color;
	return;
}


/**
 * @brief y = y1 + ((x-x1) * (y2-y1) / (x2-x1))
 *
 * @param pixel 
 * @param f 
 * @return 
 */
t_complex map_complex(t_complex *pixel, t_fractal *f)
{
	t_complex map_complex;
	/*
	   map_complex.x = ((scale_linear(pixel.x, f.minmax, f.screensize) * f.zoom)
	   + f.shift.x) ; map_complex.y = ((scale_linear(pixel.y, f.minmax,
	   f.screensize) * f.zoom) + f.shift.y) ; map_complex.x = scale_linear(double
	   n, t_complex new_minmax, t_complex old_minmax)
	   */
	/*
	*/
	 map_complex.x = scale_linear(pixel->x, f->minmax, f->screensize) *
		 f->zoom +
		 f->shift.x;
	map_complex.y = scale_linear(pixel->y, f->minmax, f->screensize) *
		 f->zoom +
		 f->shift.y;
	/*map_complex.x = f->minmax.y +
		(pixel->x / WIDTH * (f->minmax.x - f->minmax.y) *
	//(((pixel->x * f->minmax.x - f->minmax.y) / WIDTH + f->minmax.y) *
		 f->zoom +
		 f->shift.x);
	map_complex.y =
		(pixel->y / HEIGHT * (f->minmax.x - f->minmax.y) *
		//(((pixel->y * f->minmax.x - f->minmax.y) / HEIGHT + f->minmax.y) *
		f->zoom +
		f->shift.y);
*/
	return (map_complex);
}

void init_constant(t_fractal *f, t_complex *c, t_complex *z)
{
	if (*f->name != 'j')
	{
		c->x = z->x;
		c->y = z->y;
	}
}

void place_pixel(t_fractal *f, t_complex *pixel)
{
	t_complex z;
//	t_complex c;
	t_complex zprime;
	int i;
	//  z.x = ((scale_linear(pixel.x, f.minmax, f.screensize) * f.zoom) +
	//  f.shift.x) ; z.y = ((scale_linear(pixel.y, f.minmax, f.screensize) *
	//  f.zoom) + f.shift.y) ;
	zprime = (t_complex){1.0, 0.0};
	z = map_complex(pixel, f);
	f->c = z; //(t_complex){};
	i = -1;
	if (is_in_mandelbrot_set(z.x, z.y))  //&& *f.name =='m'
	{

		//	printf("\nz: %f %f,  c: %f %f,  pix: %f %f", z.y, z.x, c.y, c.x, pixel->x, pixel->y);
		return (my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK));
	}
	while (i++ < f->iterations)
	{
		if (pow(z.y, 2) + pow(z.x, 2) > f->escape)
		{
			return	my_mlx_pixel_put(&f->img, pixel->x, pixel->y, normal_color(z, zprime, f));
		}
		zprime = (t_complex){2 * z.x * zprime.x - 2 * z.y * zprime.y,
			2 * z.x * zprime.y + 2 * z.y * zprime.x};
		z = ft_complex_sum(ft_complex_sqrd(z), f->c); // z^2 +c
	}
	my_mlx_pixel_put(&f->img, pixel->x, pixel->y, LIME_SHOCK);
}

void render_f(t_fractal *f)
{

	{
		int x;
		int y;
		t_complex pixel;

		(pixel.y) = -1.0;
		while (++pixel.y < HEIGHT)
		{
			ft_putnbr_fd(pixel.y, 1);
			ft_putchar_fd(' ', 1);
			//ft_putchar_fd('', 1);
			pixel.x = -1.0;
			while (++pixel.x < WIDTH)
			{
				//ft_putnbr_fd(pixel.x, 1);
				place_pixel(f, &pixel);
			}
		}
		mlx_put_image_to_window(f->mlx_connection, f->mlx_window, f->img.img, 0, 0);
		mlx_string_put(f->mlx_connection, f->mlx_window, 20, 30, 0XFFFFFF - WHITE,
				"Help: h");
	}
	return;
}
