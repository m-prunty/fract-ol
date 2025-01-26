/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:25:17 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/25 19:12:44 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
