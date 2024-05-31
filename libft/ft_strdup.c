/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:53:19 by mprunty           #+#    #+#             */
/*   Updated: 2023/11/28 01:55:48 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		n;
	int		i;

	i = 0;
	n = ft_strlen(s) + 1;
	s2 = malloc(n * sizeof(const char));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
/*
int main()
{
	char * s = "fgdfg";
	char * ft_sd = ft_strdup(s);
	char * sd = strdup(s);

	printf("%s, %s",sd, ft_sd);
}
*/
