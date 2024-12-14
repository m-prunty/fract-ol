#include "../include/fractol.h"
#include <stdio.h>

static unsigned long int next = 1;


int	error_code(int i)
{
    if (i==0)
        return(0);
    ft_putendl_fd("Error", 2);
    if (i == 1)
        printf("%s","malloc failed");
    else if (i == 2)
        printf("%s","lst len is to short");
    else if (i == 3)
        printf("%s","mlx_window error");
    else if (i == 4)
        printf("%s","mlx_display error");
    else if (i == 5)
        printf("%s","push failed");
    else if (i == 6)
        printf("%s","turk sort failed");
    return (0);
}

int ft_rand(void)  /* RAND_MAX assumed to be 32767. */
{
    next = next * 1103515245 + 12345;
    return (unsigned)(next/65536) % RAND_MAX;// 32768;
}

void ft_srand(unsigned seed)
{
    next = seed;
}


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
/*
 *  x^2 + y^2 +  2xyi
 *  |       \   \   \
 *    Real      imAGINERY
 */
int draw_line(void *mlx,  int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX; // 10
    double deltaY = endY - beginY; // 0
    int pixels = ft_sqrtbs((deltaX * deltaX) + (deltaY * deltaY));

    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
        my_mlx_pixel_put(mlx,  pixelX, pixelY, color);
        pixelX += deltaX / pixels;
        pixelY += deltaY / pixels;
        --pixels;
    }

    return 0;
}

/*
 * set to n_error to -1 if no error
 */
int clean_fractal(t_fractal *f, int n_error)
{
    if (n_error >= 0 )
        error_code(n_error);
    if ((f->mlx_window))
        mlx_destroy_window(f->mlx_connection, f->mlx_window);
    if ((f->img.img))
        mlx_destroy_display(f->mlx_connection);
    free(f->mlx_connection);
    return (1); 
}
double	ft_atof(const char *nptr)
{
	int	n;
	double	res;
	int	neg;
    int decimal;

	n = ft_strlen(nptr)+ 1;
	res = 0;
	neg = 1;
    decimal = 0;
	while (ft_isblank(*nptr))
		nptr ++;
	if (nptr[0] == '-' || nptr[0] == '+')
	{
		if (nptr[0] == '-')
			neg *= -1;
		nptr++;
		n--;
	}
    while (ft_isdigit(*nptr))
    {
        if (!decimal)
            res = res *  10 + (*nptr - 48);
        else
            res += pow(10,-decimal++) * (*nptr - 48);
        if ( *++nptr == '.' && !decimal++)
            ++nptr;
    }
    return (res * neg);
}

int	main(int ac, char **av)
{
    t_fractal   f;
    if (!(ac >=2) || ! ((*(av++)) && (**av == 'j' || **av == 'm')))
        return (0);
    // set = **av;
    f.name = *av++;
    if (*f.name == 'j')
    {
        f.c.x = ft_atof(*av++);
        f.c.y = ft_atof(*av);
    }
    else
    {
        f.c.x = 0; 
        f.c.y = 0;
    }
    init_f(&f);
    printf("\n%f %f",f.c.x,f.c.y);
    render_f(&f);
    mlx_loop(f.mlx_connection);


    clean_fractal(&f, -1);
    /*
     * double i = 0;
     * while (i++ < 800)
        printf("\n%f", scale_linear(i, -2, 2));
    */
    printf("\n%f",pow(3,2));
    printf("\n%f",pow(7, 10));
    printf("\n%f",pow(-5, 3));
    printf("\n%f",ft_sqrtbs(7));
    printf("\n%f",ft_sqrtbs(9));
    printf("\n%f",ft_sqrtbs(2));
    printf("\n%f",pow(10, -3));
    printf("\n%f",pow(-5, -6));
    printf("\n%f %f",f.c.x,f.c.y);
    //printf("%f",ft_sqrt(-3));
    return (0);
}

/* f(z) = z^2 + c
 * z = 0, c = 1
 * = f(0) = 0^2 + 1

*/
