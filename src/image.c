/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mprunty <mprunty@student.42london.com>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/09 11:37:23 by mprunty		   #+#	#+#			 */
/*   Updated: 2025/01/21 01:10:40 by mprunty          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */
#include "fractol.h"
#include <math.h>

int	linear_interpolation(double t, t_fractal *f)
{
	int	r;
	int	g;
	int	b;

	t = t * 2 * M_PI + f->colour_shift;
	r = (sin(t) + 1) * 127;
	g = (sin(t + 2 * FT_PI_3) + 1) * 127;
	b = (sin(t + 4 * FT_PI_3) + 1) * 127;
	return ((r << 16) | (g << 8) | b);
}

double	smooth(int i, t_complex z)
{
	return (i + 1 - log(log(z.x * z.x + z.y * z.y)) / log(2));
}

int	is_mandelbulb(double x, double y)
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
	int	dst;

	dst = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	*(unsigned *)(data->pxl_addr + dst) = color;
	return ;
}

t_complex	map_complex(t_complex *pixel, t_fractal *f)
{
	t_complex	map;

	map.x = ((pixel->x / WIDTH) * f->minmax.x + f->minmax.y )
		* f->zoom + f->shift.x;
	map.y = ((pixel->y / HEIGHT) * f->minmax.x + f->minmax.y)
		* f->zoom + f->shift.y;
	return (map);
}

void	place_pixel(t_fractal *f, t_complex *pixel)
{
	t_complex	z;
	t_complex	zprime;
	t_complex	c;
	int			i;

	if (*f->name == 'm' )
	{
		z = (t_complex){0.0, 0.0};
		c = map_complex(pixel, f);
	}
	else
	{
		z = map_complex(pixel, f);
		c = f->c;
	}
	i = 0;
	while (i++ < f->iters)
	{
		if (*f->name == 'm' && is_mandelbulb(z.x, z.y))
			my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
		else if ((z.x * z.x + z.y * z.y) > f->esc)
			return (my_mlx_pixel_put(&f->img, pixel->x, pixel->y,
					linear_interpolation(smooth(i, z) / f->iters , f)));
		zprime.x = z.x * z.x - z.y * z.y + c.x;
		zprime.y = 2 * z.x * z.y + c.y;
		z = zprime;
		i++;
	}
	my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
}

void	render_chunk(t_fractal *f, int chunk_x, int chunk_y)
{
	t_complex	pixel;

	pixel.y = chunk_y;
	while (pixel.y < fmin(chunk_y + CHUNKS, HEIGHT) )
	{
		pixel.x = chunk_x;
		while (pixel.x < fmin(chunk_x + CHUNKS, WIDTH))
		{
			pixel.x++;
			place_pixel(f, &pixel);
		}
		pixel.y++;
	}
}

/**
 * @brief 
 *
 * @param f 
 */

void	clear_sidebar(t_fractal *f)
{
	int	x;
	int	y;

	y = 0;
	while (y <  HEIGHT)
	{
		x = WIDTH;
		while (x < WIDTH + SWIDTH)
		{
			my_mlx_pixel_put(&f->side, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->side.img, WIDTH , 0);
}

int	sidestr_help(t_fractal *f)
{
	f->help = (char **)malloc(sizeof(char *) * 12);
	f->help[0] = "Controls:";
	f->help[1] = "ESC - Exit";
	f->help[2] = "Arrow keys - Move view";
	f->help[3] = "Mouse wheel - Zoom in/out";
	f->help[4] = "Left click & drag - Select zoom area";
	f->help[5] = "+/- - Increase/decrease iterations";
	f->help[6] = "r - Reset view";
	f->help[7] = "h - Toggle help";
	f->help[8] = "o - Toggle sidebar";
	f->help[9] = "m, j, s - Mandelbrot, Julia, Serpinksi";
	f->help[10] = "space - Change colour";
	f->help[11] = "";
	return (11);
}

int	sidestr_info(t_fractal *f)
{
	t_infostr	data[11];
	int			i;

	i = 0;
	f->info = (char **)malloc(sizeof(char *) * 11);
	data[0] = (t_infostr){"", (t_complex){0, 0}};
	data[1] = (t_infostr){"Iterations:  ", (t_complex){f->iters, 0}};
	data[2] = (t_infostr){"Zoom:        ", (t_complex){f->zoom, 0}};
	data[3] = (t_infostr){"Shift:       ", f->shift};
	data[4] = (t_infostr){"Mouse:       ", f->mouse.start};
	data[5] = (t_infostr){"C value:     ", f->c};
	data[6] = (t_infostr){"Centre:      ", f->centre};
	data[7] = (t_infostr){"Esc:         ", (t_complex){f->esc, 0}};
	data[8] = (t_infostr){"Colour shift:", (t_complex){f->colour_shift, 0}};
	data[9] = (t_infostr){"", (t_complex){0, 0}};
	if (f->side.is_visible)
	{
		*f->info = ft_strjoin("Fractal:     ", f->name);
		while (data[++i].str)
			*(f->info + i)  = str_parsed(data[i]);
	}
	return (i);
}

void	render_sidebar(t_fractal *f)
{
	int		ilen;
	int		hlen;
	int		i;

	i = 0;
	ilen = 0;
	hlen = 0;
	clear_sidebar(f);
	if (f->side.is_visible)
		ilen = sidestr_info(f);
	if (f->show_help)
		hlen = sidestr_help(f);
	while (i < ilen || i < hlen)
	{
		if (f->side.is_visible && i < ilen)
			mlx_string_put(f->mlx_con, f->mlx_win, f->imgsize.x + 10, 
				(i * 20) + 10 , WHITE, f->info[i]);
		if (f->show_help && i < hlen)
			mlx_string_put(f->mlx_con, f->mlx_win, f->imgsize.x + 10,
				(HEIGHT - hlen * 20) + (i * 20), WHITE, f->help[i]);
		i++;
	}
}

char	*ft_dtostr(double n, int precision)
{
	char	*str;
	int		len;
	int		i;
	char	*frac;
	char	*intg;

	i = (int)(n);
	frac = ft_itoa(fabs(n - i) *pow(10, precision));
	intg = ft_itoa((int)(n));
	len = ft_strlen(intg) + precision + 2;
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, intg, len);
	if (ft_strncmp(frac, "0", len))
	{
		ft_strlcat(str, ".", len);
		ft_strlcat(str, frac, len);
	}
	free(frac);
	free(intg);
	return (str);
}


t_complex	tri_mid(t_tri tri)
{
	t_complex	mid;

	mid = (t_complex){(tri.a.x + tri.b.x + tri.c.x) / 3,
		(tri.a.y + tri.b.y + tri.c.y) / 3};
	return (mid);
}

t_complex	normalise(t_complex a, t_complex b, double mag)
{
	double	deltax;
	double	deltay;

	deltax = a.x - b.x;
	deltay = a.y - b.y;
	return ((t_complex){(deltax) / mag, (deltay) / mag});
}

void init_edges(t_triedge *e, t_complex v1, t_complex v2)
{
	double len;
	len = ft_distsqrd(v1, v2);
	e->a = sqrt(v1.y - v2.y) / len;  // negative of y component
	e->b = sqrt(v2.x - v1.x) / len;   // x component
	e->c = v1.x * v2.y - v2.x * v1.y;  
}

t_tri	*tri_def(t_tri *tri, t_complex a, t_complex b, t_complex c)
{
	tri = (t_tri *)malloc(sizeof(t_tri));
	tri->a = a;
	tri->b = b;
	tri->c = c;
	tri->mid = tri_mid(*tri);
	tri->dab = sqrt(ft_distsqrd(a, b));
	tri->dac = sqrt(ft_distsqrd(a, c));
	tri->dbc = sqrt(ft_distsqrd(b, c));
	init_edges(&tri->eab, a, b);
	init_edges(&tri->ebc, b, c);
	init_edges(&tri->eac, a, c);
	tri->xbounds = (t_complex){fmin(a.x, fmin(b.x, c.x)), fmax(a.x, fmax(b.x, c.x))};
	tri->ybounds = (t_complex){fmin(a.y, fmin(b.y, c.y)), fmax(a.y, fmax(b.y, c.y))};
	return (tri);
}
//E(x,y)=(v2.x−v1.x)(y−v1.y)−(v2.y−v1.y)(x−v1.x)
//E(x,y)=(v2.y−v1.y)x−(v2.x−v1.x)y+(v2.xv1.y−v1.xv2.y)
//E(x,y)=ax+by+c
int	edge_chk(t_complex pt, t_triedge e)
{
	double edge;
	double epsilon = 1e-10;

	edge = e.a * pt.x + e.b * pt.y + e.c;
	return (edge >= -epsilon);
}
int	tri_max(t_tri *tri, char axis)
{
	if (axis == 'y')
		return (fmax(tri->a.y, fmax(tri->b.y, tri->c.y)));
	return (fmax(tri->a.x, fmax(tri->b.x, tri->c.x)));
}

int	tri_min(t_tri *tri, char axis)
{
	if (axis == 'y')
		return (fmin(tri->a.y, fmin(tri->b.y, tri->c.y)));
	return (fmin(tri->a.x, fmin(tri->b.x, tri->c.x)));
}

void place_pixel_triangle(t_fractal *f, t_complex *pixel)
{
	t_complex point;

	point = map_complex(pixel, f);
	if (edge_chk(point, f->tri->eab) &&
			edge_chk(point, f->tri->ebc) && edge_chk(point, f->tri->eac))
	{
		my_mlx_pixel_put(&f->img, pixel->x, pixel->y, WHITE);
	}
	else 
	{
		my_mlx_pixel_put(&f->img, pixel->x, pixel->y, BLACK);
	}
}

void	set_exact(t_complex *target, t_complex *src)
{
	target->x = src->x;
	target->y = src->y;
}

void	set_midpoint(t_complex *target, t_complex *a, t_complex *b)
{
	target->x = (a->x + b->x) / 2;
	target->y = (a->y + b->y) / 2;
}

void subtriangle(t_fractal *f, t_tri *parent_tri, t_tri *t, int current_depth, int max_depth, int color)
{
	t_complex pixel;
	int start;
	int end;
	t_tri parent_a;
	t_tri parent_b;
	t_tri parent_c;
	t_tri child_a;
	t_tri child_b;
	t_tri child_c;

	pixel.y = t->a.y;
	while (pixel.y <= t->c.y && pixel.y < f->imgsize.y)
	{
		start = t->c.x - (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		end = t->c.x + (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		pixel.x = 0;
		while (pixel.x < start && pixel.x < f->imgsize.x)
		{
			pixel.x++;
		}
		while (start <= pixel.x && pixel.x <= end && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, color);
			pixel.x++;
		}
		while (pixel.x < f->imgsize.x)
		{
			pixel.x++;
		}
		pixel.y++;
	}
	if (current_depth < max_depth)
	{
		color = ((int)((color >> 16) * 0.9) << 16) + ((int)(((color >> 8) & 0xFF) * 0.9) << 8) + (int)((color & 0xFF) * 0.9);
		set_exact(&parent_a.a, &parent_tri->a);
		set_exact(&parent_a.b, &t->c);
		set_exact(&parent_a.c, &t->a);
		set_exact(&parent_b.a, &t->c);
		set_exact(&parent_b.b, &parent_tri->b);
		set_exact(&parent_b.c, &t->b);
		set_exact(&parent_c.a, &t->a);
		set_exact(&parent_c.b, &t->b);
		set_exact(&parent_c.c, &parent_tri->c);
		set_midpoint(&child_a.a, &parent_tri->a, &t->a);
		set_midpoint(&child_a.b, &t->a, &t->c);
		set_midpoint(&child_a.c, &parent_tri->a, &t->c);
		set_midpoint(&child_b.a, &t->c, &t->b);
		set_midpoint(&child_b.b, &parent_tri->b, &t->b);
		set_midpoint(&child_b.c, &parent_tri->b, &t->c);
		set_midpoint(&child_c.a, &parent_tri->c, &t->a);
		set_midpoint(&child_c.b, &parent_tri->c, &t->b);
		set_midpoint(&child_c.c, &t->a, &t->b);
		subtriangle(f, &parent_a, &child_a, current_depth + 1, max_depth, color);
		subtriangle(f, &parent_b, &child_b, current_depth + 1, max_depth, color);
		subtriangle(f, &parent_c, &child_c, current_depth + 1, max_depth, color);
	}
}

void triangle(t_fractal *f, t_tri *t)
{
	t_complex pixel;
	int start;
	int end;
	t_tri child;

	pixel.y = 0;
	while (pixel.y < t->c.y && pixel.y < f->imgsize.y)
	{
		pixel.x = 0;
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	while (pixel.y <= t->a.y && pixel.y < f->imgsize.y)
	{
		start = t->c.x - (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		end = t->c.x + (t->c.x - t->a.x) * (pixel.y - t->c.y) / (t->a.y - t->c.y);
		pixel.x = 0;
		while (pixel.x < start && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		while (start <= pixel.x && pixel.x <= end && pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, 0x444444);
			pixel.x++;
		}
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	while (pixel.y < f->imgsize.y)
	{
		pixel.x = 0;
		while (pixel.x < f->imgsize.x)
		{
			my_mlx_pixel_put(&f->img, pixel.x, pixel.y, BLACK);
			pixel.x++;
		}
		pixel.y++;
	}
	set_midpoint(&child.a, &t->a, &t->c);
	set_midpoint(&child.b, &t->b, &t->c);
	set_midpoint(&child.c, &t->a, &t->b);
	subtriangle(f, t, &child, 1, 7, RED);
}


/*
   void	triangle(t_fractal *f, t_tri *t)
   {
   t_complex	pix;

   pix.y = fmax(0, t->ybounds.x);
   while (pix.y < fmin(f->imgsize.y , t->ybounds.y))
   {
   pix.x = fmax(0, t->xbounds.x);
   while (pix.x < fmin(f->imgsize.x , t->xbounds.y))
   {
   if (edge_chk(pix, t->eab) 
   && edge_chk(pix, t->ebc)
   && edge_chk(pix, t->eac))
   {
   my_mlx_pixel_put(&f->img, pix.x, pix.y, WHITE);
   }
   pix.x++;
   }
   pix.y++;
   }
   }*/

void init_serptri(t_fractal *f)
{
	f->tri = tri_def(f->tri,
			/*map_complex(&(*/(t_complex){f->imgsize.x * 0.05, f->imgsize.y * 0.95},//), f),                  // Bottom-left
			/*map_complex(&(*/(t_complex){f->imgsize.x * 0.95, f->imgsize.y * 0.95},//), f),      // Bottom-right
			/*map_complex(&(*/(t_complex){f->imgsize.x * 0.5, f->imgsize.y * 0.05});//), f));          // Top
	f->zoom = 1.0;
	if (f->c.x > 2)
		f->iters = (int)f->c.x;
	else
		f->iters = 6;
}
/*
   void	init_serptri(t_fractal *f)
   {

//recentre(f);
//	    map_complex(&((t_complex){0, HEIGHT}), f),          // Bottom-left
// map_complex(&((t_complex){WIDTH, HEIGHT}), f),      // Bottom-right
// map_complex(&((t_complex){WIDTH * 0.5, 0}), f));
//size = map_complex(&(t_complex){WIDTH * 0.5, HEIGHT * 0.5}, f);
t_complex		size;
f->minmax = (t_complex){1.0, 0.0};
f->shift = (t_complex){0,0};
f->centre = (t_complex){0, 0};
size = (t_complex){2, 2};
f->tri = tri_def(f->tri,
(t_complex){f->centre.x - size.x, f->centre.y + size.y},
(t_complex){f->centre.x + size.x, f->centre.y + size.y},
(t_complex){f->centre.x, f->centre.y - size.y}
);
f->zoom = 1.0;
if (f->c.x > 2)
f->iters = (int)f->c.x;
else
f->iters = 6;
return ;
}
*/
/*
   void sierpinski(t_fractal *f, t_tri *t, int i)
   {
   t_tri		*sub1;
   t_tri		*sub2;
   t_tri		*sub3;

   if (i == 0)
   {
   triangle(f, t);
   return ;
   }
   t->sub1 = tri_def(sub1, t->a, t->mid, t->c);
   sub2 = tri_def(sub2, t->b, t->mid, t->c);
   sub3 = tri_def(sub3, t->a, t->b, t->mid);
   sierpinski(f, sub1, i - 1);
   sierpinski(f, sub2, i - 1);
   sierpinski(f, sub3, i - 1);
   }
   */
char*str_parsed(t_infostr info)
{
	char	*res;
	char	*x;
	char	*y;
	int		len;

	len = ft_strlen(info.str);
	x = ft_dtostr(info.c.x, 2);
	y = ft_dtostr(info.c.y, 2);
	len += ft_strlen(x) + ft_strlen(y) + 2;
	res = (char *)malloc(sizeof(char *) * len);
	ft_strlcpy(res, info.str, ft_strlen(info.str) + 1);
	if (info.c.x != 0)
	{
		ft_strlcat(res, x, len);
		if (info.c.y != 0)
		{
			ft_strlcat(res, " ", len);
			ft_strlcat(res, y, len);
		}
	}
	free(x);
	free(y);
	return (res);
}

void	render_f(t_fractal *f)
{
	int	x;
	int	y;

	if (*f->name == 's')
	{
		init_serptri(f);
		triangle(f, f->tri);
	}
	//	sierpinski(f, (t_complex){0, HEIGHT}, (t_complex){WIDTH, HEIGHT}, (t_complex){WIDTH / 2, 0}, 6);
	else
	{
		y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
				render_chunk(f, x, y);
				x += CHUNKS;
			}
			y += CHUNKS;
		}
	}
	f->centre = map_complex(&(t_complex){f->imgsize.x / 2, f->imgsize.y / 2}, f);
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->img.img, 0, 0);
	render_sidebar(f);
	return ;
}
