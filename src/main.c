/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:08:07 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/12 05:24:23 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/**
 * @brief function to handle errors
 *
 * @param i error number
 * @param info info to return about error
 * @return an int 0  
 */
int	error_func(int i, char *info)
{
	if (i == 0)
		return (0);
	ft_putendl_fd("Error", 2);
	if (i == 1)
		ft_printf("%s", "incorrect input:");
	else if (i == 2)
		ft_printf("%s", "malloc failed");
	else if (i == 3)
		ft_printf("%s", "mlx error:");
	else if (i == 4)
		ft_printf("%s", "mlx_display error");
	else if (i == 5)
		ft_printf("%s", "");
	else if (i == 6)
		ft_printf("%s", "turk sort failed");
	ft_printf("%s", info);
	return (0);
}

/**
 * @brief cleans up the fractal: destroys mlx, frees mem, and relays any error
 * 
 * @param f main t_fractal object
 * @param n_error error number set to -1 if no error 
 * @param info further info on error, leave blank if none
 */
void	clean_fractal(t_fractal *f, int n_error, char *info)
{
	if (n_error >= 0)
		error_func(n_error, info);
	if ((f->mlx_win))
		mlx_destroy_window(f->mlx_con, f->mlx_win);
	if ((f->img.img))
		mlx_destroy_display(f->mlx_con);
	if ((f->over.img))
		mlx_destroy_display(f->mlx_con);
	free(f->mlx_con);
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
	int		neg;
	int		decimal;
	double	res;

	res = 0;
	neg = 1;
	if (nptr)
	{
		decimal = 0;
		while (ft_isspace(*nptr) || (nptr[0] == '-' || nptr[0] == '+'))
			if (*nptr++ == '-')
				neg *= -1;
		while (ft_isdigit(*nptr))
		{
			if (!decimal)
				res = res * 10 + (*nptr - 48);
			else
				res += ft_pow(10, -decimal++) * (*nptr - 48);
			if (*++nptr == '.' && !decimal++)
				nptr++;
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
/*
int	ft_isnumf(char *str, t_complex sym)
{

	if (*str == '\0')
		return (1);
	if (sym.y && *str == '.')
		return (ft_isnumf(++str, (t_complex){sym.x, 0}) * 1);
	if (sym.x && *str == '-')
		return (ft_isnumf(++str, (t_complex){0, sym.y}) * 1);
	if (ft_isdigit(*str))
		return (ft_isnumf(++str, sym) * 1);
	return (0);
}*/

int	check_args(int ac, char **av, t_fractal *f)
{
	if (!(ac >= 2) || ! ((*(av++)) && (**av == 'j' || **av == 'm')))
		return (error_func(1, "enter either 'm' or 'j x y' "));
	f->name = *av++;
	if (!ft_isnumf(*av) ||!ft_isnumf(*(av + 1)))
		return (error_func(1,
				"julia set must be initialised with x y in the form 'j x y'"));
	if (*(f->name) == 'j')
		f->c = (t_complex){ft_atof(av[0]), ft_atof(av[1])};
	else
		f->c = (t_complex){0, 0};
	return (1);
}

int	main(int ac, char **av)
{
	t_fractal	f;

	if (check_args(ac, av, &f))
	{
		init_values(&f);
		init_f(&f);
		render_f(&f);
		mlx_loop(f.mlx_con);
		clean_fractal(&f, -1, "fractal exited cleanly");
	}
	return (0);
}

/* f(z) = z^2 + c
 * z = 0, c = 1
 * = f(0) = 0^2 + 1

*/
