/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:51:48 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/04 23:35:25 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	int		n;

	i = 1;
	start = 0;
	end = 0;
	n = ft_strlen(s1);
	while (i <= n)
	{
		if (!ft_strchr(set, s1[i - 1]) && !start)
			start = i;
		if (!ft_strchr(set, s1[n - i]) && !end)
			end = n - i + 1;
		i++;
	}
	if (start && end)
		return (ft_substr(s1, start - 1, end - start + 1));
	return (ft_substr(s1, 0, 0));
}
