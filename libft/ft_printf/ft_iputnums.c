/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iputnums.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:18:02 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/12 22:56:07 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

int	ft_iputnum(long long n, int base, int caps)
{
	int		count;
	char	*symbols;	

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		ft_iputchar('-');
		return (ft_iputnum(-n, base, caps) + 1);
	}
	if (n < base && !caps)
		return (ft_iputchar(symbols[n]));
	else if (n < base && caps)
		return (ft_iputchar(ft_toupper(symbols[n])));
	else
	{
		count = ft_iputnum(n / base, base, caps);
		return (count + ft_iputnum(n % base, base, caps));
	}
}

int	ft_iputnum_ptr(size_t n)
{
	size_t	base;
	int		count;
	char	*symbols;	

	symbols = "0123456789abcdef";
	base = 16;
	if (n < base)
		return (ft_iputchar(symbols[n]));
	else
	{
		count = ft_iputnum_ptr(n / base);
		return (count + ft_iputnum_ptr(n % base));
	}
}

int	ft_iputptr(size_t argp)
{
	int				count;

	count = 0;
	if (!argp)
	{
		count += ft_iputstr("(nil)");
		return (count);
	}
	count += ft_iputstr("0x");
	count += ft_iputnum_ptr(argp);
	return (count);
}
