/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:35:15 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/06 19:52:14 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	n;

	n = ft_strlen(s) + 1;
	return ((char *)ft_memchr(s, c, n));
}
/*
int main()
 {
     char *s = ft_strchr("acdbchjk", 'k');
     printf("\n%s",s);
 }
*/
