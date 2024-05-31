/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:53:50 by mprunty           #+#    #+#             */
/*   Updated: 2024/04/15 18:53:59 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

dl_list	*ft_dllstnew(void *content)
{
	dl_list	*elt;

	if (!(elt = (dl_list*)malloc(sizeof(*elt))))
		return (NULL);
	elt->content = content;
	elt->next = NULL;
	elt->prev = NULL;
	elt->idx = 0;
	return (elt);
}
