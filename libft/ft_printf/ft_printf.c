/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:18:31 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/12 22:49:30 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

int	_ftprintf_parse(char spec, va_list argp)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_iputchar(va_arg(argp, int));
	else if (spec == '%')
		count += ft_iputchar('%');
	else if (spec == 's')
		count += ft_iputstr(va_arg(argp, char *));
	else if (spec == 'd' || spec == 'i')
		count += ft_iputnum((long)(va_arg(argp, int)), 10, 0);
	else if (spec == 'u')
		count += ft_iputnum((long long)(va_arg(argp, unsigned int)), 10, 0);
	else if (spec == 'x')
		count += ft_iputnum((long long)(va_arg(argp, unsigned int)), 16, 0);
	else if (spec == 'X')
		count += ft_iputnum((long long)(va_arg(argp, unsigned int)), 16, 1);
	else if (spec == 'p' )
		count += ft_iputptr(va_arg(argp, size_t));
	else
	{
		count += ft_iputchar('%');
		count += ft_iputchar(spec);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	argp;
	int		count;

	va_start(argp, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += _ftprintf_parse(*(++format), argp);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(argp);
	return (count);
}
