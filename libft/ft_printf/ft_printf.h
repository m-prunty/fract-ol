/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:42:32 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/10 14:16:42 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_PRINTF_H
# define FT_PRINTF_H 

# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include "libft.h"
/*typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
*/
int	ft_iputnum(long long n, int base, int caps);
int	ft_iputnum_ptr(size_t n);
int	ft_iputptr(size_t argp);
int	ft_iputchar(int c);
int	ft_iputstr(char *str);
int	ft_printf(const char *format, ...);

#endif
