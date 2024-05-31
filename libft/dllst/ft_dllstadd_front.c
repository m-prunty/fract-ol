/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:50:56 by mprunty           #+#    #+#             */
/*   Updated: 2024/04/15 18:51:09 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dllstadd_front(dl_list **alst, dl_list *new)
{
	if (alst)
	{
		if (*alst)
		{
			new->next = *alst;
			new->prev = *alst->prev
			*alst->prev = new;
			*alst->idx = 0;
		}
		*alst = new;
		*alst->idx = 1;
	}
}
