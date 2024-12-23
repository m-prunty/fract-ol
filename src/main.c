/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:22:08 by potz              #+#    #+#             */
/*   Updated: 2024/12/23 20:32:56 by potz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <stdio.h>

/**
 * @brief function to handle errors
 *
 * @param i error number
 * @param info info to return about error
 * @return an int 0  
 */
int	error_func(int i, char *info)
{

	if (i==0)
		return (0);
	ft_putendl_fd("Error", 2);
	if (i == 1)
		ft_printf("%s","incorrect input:");
	else if (i == 2)
		ft_printf("%s","malloc failed");
	else if (i == 3)
		ft_printf("%s","mlx error:");
	else if (i == 4)
		ft_printf("%s","mlx_display error");
	else if (i == 5)
		ft_printf("%s","");
	else if (i == 6)
		ft_printf("%s","turk sort failed");
	ft_printf("%s", info);
	return (0);
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

/**
 * @brief cleans up the fractal: destroys mlx, frees mem, and relays any error
 * 
 * @param f main t_fractal object
 * @param n_error error number set to -1 if no error 
 * @param info further info on error, leave blank if none
 */
void    clean_fractal(t_fractal *f, int n_error, char *info)
{
	if (n_error >= 0 )
		error_func(n_error, info); 
	if ((f->mlx_window))
		mlx_destroy_window(f->mlx_connection, f->mlx_window);
	if ((f->img.img))
		mlx_destroy_display(f->mlx_connection);
	free(f->mlx_connection);
	return ; 
}


/**
 * @brief converts a string to float 
 *
 * @param nptr string to convert
 * @return a double of the string converted
 */
double	ft_atof(const char *nptr)
{
	int	n;
	double	res;
	int	neg;
	int decimal;

	res = 0;
	neg = 1;
	if (nptr){
		n = ft_strlen(nptr)+ 1;
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
				res += ft_pow(10,-decimal++) * (*nptr - 48);
			if ( *++nptr == '.' && !decimal++)
				++nptr;
		}
	}
	return (res * neg);
}


/**
 * @brief function to check if a string value is a float
 *
 * @param str string to check
 * @param dec boolean switch to deal with a single decimal point 
 * @return 1 if isnum else 0
 */
int ft_isnumf(char *str, int dec)
{
	if (*str == '\0')
		return (1);
	if (dec && *str == '.')
		return (ft_isnumf(++str, 0) * 1);
	if (ft_isdigit(*str))
		return (ft_isnumf(++str, dec) * 1);
	return (0);
}


int	main(int ac, char **av)
{
	t_fractal   f;
	if (!(ac >=2) || ! ((*(av++)) && (**av == 'j' || **av == 'm')))
		return (error_func(1, "enter either 'm' or 'j x y' "));
	// set = **av;
	f.name = *av++;
	if ((*f.name == 'j') && (!ft_isnumf(*av, 1) || !ft_isnumf(*(av + 1), 1)) )
		return (error_func(1, "'j' julia set must be seeded with initial values x y in the form 'j x y'"  ));
	init_values(&f, av);
	init_f(&f);
	printf("\n%f %f",f.c.x,f.c.y);
	render_f(&f);
	mlx_loop(f.mlx_connection);


	clean_fractal(&f, -1, "");
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
