/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:55:27 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/04 21:49:18 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isblank(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	res;
	int	neg;

	n = ft_strlen(nptr)+ 1;
	res = 0;
	neg = 1;
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
		if (ft_isdigit(*nptr))
			res = res * 10 + (*nptr - 48);
		nptr++;
	}
	return (res * neg);
}
