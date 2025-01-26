/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:08:07 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 08:24:41 by mprunty          ###   ########.fr       */
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
		ft_putstr_fd(ERR_INPUT, 2);
	else if (i == 2)
		ft_putstr_fd(ERR_MALLOC, 2);
	else if (i == 3)
		ft_putstr_fd(ERR_MLX, 2);
	ft_putendl_fd(info, 1);
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
	int	i;

	i = 12;
	if (n_error >= 0)
		error_func(n_error, info);
	if ((f->mlx_win))
		mlx_destroy_window(f->mlx_con, f->mlx_win);
	if ((f->img.img))
		mlx_destroy_image(f->mlx_con, f->img.img);
	if ((f->side.img))
		mlx_destroy_image(f->mlx_con, f->side.img);
	if (f->mlx_con)
		mlx_destroy_display(f->mlx_con);
	if (f->info)
		while (f->info[i])
			free(f->info[i]);
	if (f->tri)
		clean_tri(f->tri);
	free(f->help);
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
				res += pow(10, -decimal++) * (*nptr - 48);
			if (*++nptr == '.' && !decimal++)
				nptr++;
		}
	}
	return (res * neg);
}

int	check_args(int ac, char **av, t_fractal *f)
{
	if (!(ac >= 2)
		|| ! ((*(av++)) && (**av == 'j' || **av == 'm' || **av == 's')))
		return (error_func(1, ERR_INPUT_VAL));
	f->name = *av++;
	if (*f->name == 'j' || *f->name == 's')
	{
		if (!ft_isnumf(*av) || (*f->name == 'j' && !ft_isnumf(*(av + 1))))
			return (error_func(1, ERR_INPUT_XY));
		f->c = (t_complex){ft_atof(av[0]), ft_atof(av[1])};
	}
	else
		f->c = (t_complex){0, 0};
	return (1);
}

int	main(int ac, char **av)
{
	t_fractal	f;

	ft_bzero(&f, sizeof(t_fractal));
	if (check_args(ac, av, &f))
	{
		init_values(&f);
		init_f(&f);
		pre_calc(&f, &f.img);
		render_f(&f);
		mlx_loop(f.mlx_con);
	}
	return (0);
}
