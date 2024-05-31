/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:59:02 by mprunty           #+#    #+#             */
/*   Updated: 2023/11/28 01:12:17 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *ptr, int value, int num)
{
	char	*ptr2;
	int		i;

	ptr2 = (char *)ptr;
	i = 0;
	while (i < num)
		ptr2[i++] = (char)value;
	return (ptr);
}
