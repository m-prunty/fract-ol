/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:25:17 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 11:45:18 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	set_exact(t_complex *target, t_complex *src)
{
	target->x = src->x;
	target->y = src->y;
}

void	set_midpoint(t_complex *target, t_complex *a, t_complex *b)
{
	target->x = (a->x + b->x) / 2;
	target->y = (a->y + b->y) / 2;
}

void	set_triangles(t_tri *parent, t_tri *child, t_tri *t, t_tri *parent_tri)
{
	set_exact(&parent[0].a, &parent_tri->a);
	set_exact(&parent[0].b, &t->c);
	set_exact(&parent[0].c, &t->a);
	set_exact(&parent[1].a, &t->c);
	set_exact(&parent[1].b, &parent_tri->b);
	set_exact(&parent[1].c, &t->b);
	set_exact(&parent[2].a, &t->a);
	set_exact(&parent[2].b, &t->b);
	set_exact(&parent[2].c, &parent_tri->c);
	set_midpoint(&child[0].a, &parent_tri->a, &t->a);
	set_midpoint(&child[0].b, &t->a, &t->c);
	set_midpoint(&child[0].c, &parent_tri->a, &t->c);
	set_midpoint(&child[1].a, &t->c, &t->b);
	set_midpoint(&child[1].b, &parent_tri->b, &t->b);
	set_midpoint(&child[1].c, &parent_tri->b, &t->c);
	set_midpoint(&child[2].a, &parent_tri->c, &t->a);
	set_midpoint(&child[2].b, &parent_tri->c, &t->b);
	set_midpoint(&child[2].c, &t->a, &t->b);
}
