/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 20:17:23 by nboste            #+#    #+#             */
/*   Updated: 2018/01/24 16:19:59 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_utility.h"
#include <math.h>

// Commented by ada-cunh: On garde le vecteur 1:1 pour avoir la direction
void	normalize_vector(t_point *p)
{
	double  len;

	len = sqrt((p->x * p->x) + (p->y * p->y) + (p->z * p->z));
	p->x = p->x / len;
	p->y = p->y / len;
	p->z = p->z / len;
}

double	vector_multiply(t_point p1, t_point p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

t_point	vector_mul(t_point p1, double d)
{
	t_point p;

	p.x = p1.x * d;
	p.y = p1.y * d;
	p.z = p1.z * d;
	return (p);
}

t_point	vector_add(t_point p1, t_point p2)
{
	t_point p;

	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	p.x = p1.z + p2.z;
	return (p);
}

t_point	vector_sub(t_point p1, t_point p2)
{
	t_point	p;

	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return (p);
}

double	vec_dist(t_point p1, t_point p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z)));
}

double	get_norm(t_point p)
{
	return (sqrt((p.x * p.x) + (p.y * p.y) + (p.z * p.z)));
}

double	calc_dist(t_point a, t_point b)
{
	return (sqrt(((a.x - b.x) * (a.x - b.x)) +
				((a.y - b.y) * (a.y - b.y)) +
				((a.z - b.z) * (a.z - b.z))));
}

float	get_angle(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
