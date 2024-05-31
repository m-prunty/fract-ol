/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:38:34 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/05 17:29:35 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

int	get_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		n1;
	int		n2;
	int		i;
	int		ilen;

	i = 0;
	n1 = (ft_strlen(s1));
	n2 = (ft_strlen(s2));
	ilen = get_max(n1, n2);
	join = (char *)malloc((n1 + n2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	while (i < ilen)
	{
		if (n1-- > 0)
			join[i] = s1[i];
		i++;
		if (n2-- > 0)
			join[n1 + (2 * i - 1)] = s2[i - 1];
	}
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (join);
}
/*
int main()
{
        char * s = "fgdfghhg";
	char * s2 = "aaaxcc";
        printf("%s",ft_strjoin(s,s2));
        return 0;
}
*/
