/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:06:05 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/07 10:10:01 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	n = ft_strlen(little);
	if (!n || big == little)
		return ((char *)(big));
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j]
			&& little[j] && i + j < len)
			j++;
		if (j == n)
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
/*
int	main()
{
    char haystack[30] = "aaabcabcd";
    char needle[10] = "aabc";
    char * empty = (char*)"";

	//char *res = ft_strnstr(haystack, needle, 0);
	char *res = ft_strnstr(haystack, "c", -1); 
	char *res2 = strnstr(haystack, "c", -1); 
	//char *res = ft_strnstr(empty, "", 0);
	printf(":%s:%s:", res, res2);
}
*/
