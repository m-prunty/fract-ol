/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:17:41 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/07 10:11:09 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
#include <stdio.h> 
int main()
{
	char dest[30]; memset(dest, 'C', 5);
	char * src = (char *)"AAAAAAAAA";
	//dest[0] = 'B';
//	printf("%i, %s", ft_strlcat(dest, "lorem ipsum dolor sit amet", 0), dest);
	int i=ft_strlcat(dest, src, -1);
	printf("%s, %i ", dest,i);
//	printf("%i",strlcat("abc", NULL, 0));
//	printf("%i",ft_strlcat("abc", NULL, 0));
}*/
