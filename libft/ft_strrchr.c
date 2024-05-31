/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:35:35 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/07 10:03:26 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = ft_strlen(s);
	while (n >= 0)
	{
		if (*(s + n) == (char)c)
			return ((char *)s + n);
		n--;
	}
	return (0);
}
/*
int main()
{
	char	str2[] = "bonjour";
	char	str3[] = "";

	printf("%s", ft_strrchr(str2, '\0'));
	printf("%s", ft_strrchr(str3, '\0'));
//	char *s = ft_strrchr("acdbkchjk", 'k');
//	printf("\n%s",s);
}
*/
