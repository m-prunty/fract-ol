/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:25:17 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/26 16:12:40 by mprunty          ###   ########.fr       */
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
/*
t_complex	tri_mid(t_tri tri)
{
	t_complex	mid;

	mid = (t_complex){(tri.a.x + tri.b.x + tri.c.x) / 3,
		(tri.a.y + tri.b.y + tri.c.y) / 3};
	return (mid);
}

t_complex	normalise(t_complex a, t_complex b, double mag)
{
	double	deltax;
	double	deltay;

	deltax = a.x - b.x;
	deltay = a.y - b.y;
	return ((t_complex){(deltax) / mag, (deltay) / mag});
}

void	init_edges(t_triedge *e, t_complex v1, t_complex v2)
{
	double	len;

	len = ft_distsqrd(v1, v2);
	e->a = sqrt(v1.y - v2.y) / len;
	e->b = sqrt(v2.x - v1.x) / len;
	e->c = v1.x * v2.y - v2.x * v1.y;
}
*/
/*
t_tri	*tri_def(t_tri *tri, t_complex a, t_complex b, t_complex c)
{
	tri = (t_tri *)malloc(sizeof(t_tri));
	tri->a = a;
	tri->b = b;
	tri->c = c;
	tri->mid = tri_mid(*tri);
	tri->dab = sqrt(ft_distsqrd(a, b));
	tri->dac = sqrt(ft_distsqrd(a, c));
	tri->dbc = sqrt(ft_distsqrd(b, c));
	init_edges(&tri->eab, a, b);
	init_edges(&tri->ebc, b, c);
	init_edges(&tri->eac, a, c);
	tri->xbounds = (t_complex){fmin(a.x, fmin(b.x, c.x)),
		fmax(a.x, fmax(b.x, c.x))};
	tri->ybounds = (t_complex){fmin(a.y, fmin(b.y, c.y)),
		fmax(a.y, fmax(b.y, c.y))};
	return (tri);
}
*/
/*
//E(x,y)=(v2.x−v1.x)(y−v1.y)−(v2.y−v1.y)(x−v1.x)
//E(x,y)=(v2.y−v1.y)x−(v2.x−v1.x)y+(v2.xv1.y−v1.xv2.y)
//E(x,y)=ax+by+c
int	edge_chk(t_complex pt, t_triedge e)
{
	double	edge;
	double	epsilon;

	epsilon = 1e-10;
	edge = e.a * pt.x + e.b * pt.y + e.c;
	return (edge >= -epsilon);
}

int	tri_max(t_tri *tri, char axis)
{
	if (axis == 'y')
		return (fmax(tri->a.y, fmax(tri->b.y, tri->c.y)));
	return (fmax(tri->a.x, fmax(tri->b.x, tri->c.x)));
}

int	tri_min(t_tri *tri, char axis)
{
	if (axis == 'y')
		return (fmin(tri->a.y, fmin(tri->b.y, tri->c.y)));
	return (fmin(tri->a.x, fmin(tri->b.x, tri->c.x)));
}*/
