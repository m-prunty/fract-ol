#include "../include/fractol.h"

double	ft_complex_abs(t_complex complex)
{
	return (sqrt(complex.x * complex.x + complex.y * complex.y));
}

double	ft_complex_dot(t_complex *a, t_complex *b)
{
	return (a->x * b->x + a->y * b->y);
}

void	ft_complex_exp(double angle, t_complex *result)
{
	double	magnitude;

	magnitude = exp(angle);
	result->x = magnitude * cos(angle);
	result->y = magnitude * sin(angle);
}

t_complex	ft_complex_conjugate(t_complex a)
{
	t_complex	result;

	result.x = a.x;
	result.y = -a.y;
	return (result);
}

t_complex	ft_complex_divide(t_complex numerator, t_complex denominator)
{
	t_complex	result;
	t_complex	denom_conjugate;
	t_complex	num_mult;
	double		denom_mult;

	denom_conjugate = ft_complex_conjugate(denominator);
	num_mult = (t_complex){numerator.x * denom_conjugate.x - numerator.y
		* denom_conjugate.y, numerator.x * denom_conjugate.y + numerator.y
		* denom_conjugate.x};
	denom_mult = denominator.x * denominator.x + denominator.y * denominator.y;
	result.x = num_mult.x / denom_mult;
	result.y = num_mult.y / denom_mult;
	return (result);
}
