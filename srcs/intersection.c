/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:52:08 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/24 18:07:59 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vector_utility.h"

static double	get_delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}
/*
static double dotProduct(t_point p1, t_point p2)
{
	double n1;
	double n2;

	normalize_vector(&p1);
	normalize_vector(&p2);
	n1 = get_norm(p1);
	n2 = get_norm(p2);
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
} */

static t_bool   inter_cylinder(t_ray r, t_object *obj, t_point *inter)
{
	t_point pos;
	t_point dir;
	t_point poly;
	double  delta;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	poly.x = (dir.x * dir.x + dir.y * dir.y);
	poly.y = 2 * dir.x * pos.x + 2 * dir.y * pos.y;
	poly.z = pow(pos.x, 2) + pow(pos.y, 2) - pow(obj->radius, 2);
	delta = get_delta(poly.x, poly.y, poly.z);
	if (delta < 0)
		return (0);
	else
	{
		inter->x = (-poly.y + sqrt(delta)) / (2 * poly.x);
		inter->y = (-poly.y - sqrt(delta)) / (2 * poly.x);
		if (inter->x < inter->y)
		{
			inter->y = r.pos.y + r.dir.y * inter->x;
			inter->z = r.pos.z + r.dir.z * inter->x;
			inter->x = r.pos.x + r.dir.x * inter->x;
		}
		else
		{
			inter->x = r.pos.x + r.dir.x * inter->y;
			inter->z = r.pos.z + r.dir.z * inter->y;
			inter->y = r.pos.y + r.dir.y * inter->y;
		}
		return (1);
	}
}

static t_bool          inter_cone(t_ray r, t_object *obj, t_point *inter)
{
	t_point pos;
	t_point dir;
	t_point poly;
	double  delta;
	double	radius;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	radius = sin(ft_degtorad(obj->radius)) * sin(ft_degtorad(obj->radius));
	poly.x = (dir.x * dir.x) + (dir.y * dir.y) - (dir.z * dir.z * radius);
	poly.y = 2 * ((dir.x * pos.x) + (dir.y * pos.y) - (radius * dir.z * pos.z));
	poly.z = pow(pos.x, 2) + pow(pos.y, 2) - pow(pos.z, 2) * radius;
	delta = get_delta(poly.x, poly.y, poly.z);
	if (delta < 0)
		return (0);
	else
	{
		inter->x = (-poly.y + sqrt(delta)) / (2 * poly.x);
		inter->y = (-poly.y - sqrt(delta)) / (2 * poly.x);
		if (inter->x < inter->y)
		{
			inter->y = r.pos.y + r.dir.y * inter->x;
			inter->z = r.pos.z + r.dir.z * inter->x;
			inter->x = r.pos.x + r.dir.x * inter->x;
		}
		else
		{
			inter->x = r.pos.x + r.dir.x * inter->y;
			inter->z = r.pos.z + r.dir.z * inter->y;
			inter->y = r.pos.y + r.dir.y * inter->y;
		}
		return (1);
	}
}

static t_bool	inter_sphere(t_ray r, t_object *obj, t_point *inter)
{
	t_point		dir;
	t_point		pos;
	t_point		opos;
	t_point		poly;
	double		delta;

	dir = r.dir;
	pos = r.pos;
	opos = obj->pos;
	poly.x = (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	poly.y = 2 * (dir.x * (pos.x - opos.x) + dir.y * (pos.y - opos.y) + dir.z * (pos.z - opos.z));
	poly.z = (pow(pos.x + opos.x, 2) + pow(pos.y - opos.y, 2) + pow(pos.z - opos.z, 2) - (obj->radius * obj->radius));
	delta = get_delta(poly.x, poly.y, poly.z);
	if (delta < 0)
		return (0);
	else
	{
		inter->x = (-poly.y + sqrt(delta)) / (2 * poly.x);
		inter->y = (-poly.y - sqrt(delta)) / (2 * poly.x);
		if (inter->x < inter->y)
		{
			inter->y = r.pos.y + r.dir.y * inter->x;
			inter->z = r.pos.z + r.dir.z * inter->x;
			inter->x = r.pos.x + r.dir.x * inter->x;
		}
		else
		{
			inter->x = r.pos.x + r.dir.x * inter->y;
			inter->z = r.pos.z + r.dir.z * inter->y;
			inter->y = r.pos.y + r.dir.y * inter->y;
		}
		return (1);
	}
}

static t_bool	inter_plan(t_ray r, t_object *obj, t_point *inter)
{
	t_point	n;
	t_point	l;
	double	m;
	double	t;
	double	d;
	t_point pos;

	n = obj->normal;
	normalize_vector(&n);
	m = vector_multiply(n, r.dir);
	if (fabs(m) < 0.000001)
		return (0);
	l = vector_sub(r.pos, obj->pos);
	d = vector_multiply(n, l);
	t = -d / m;
	pos = vector_add(r.pos, vector_mul(r.dir, t));
	if (t <= 0.000001)
		return (0);
	else
	{
		inter->x = r.pos.x + t * r.dir.x;
		inter->y = r.pos.y + t * r.dir.y;
		inter->z = r.pos.z + t * r.dir.z;
		return (1);
	}
	return (0);
}

t_bool			intersection(t_ray r, t_object *obj, t_point *inter)
{
	if (obj->type == sphere)
		return (inter_sphere(r, obj, inter));
	else if (obj->type == plan)
		return (inter_plan(r, obj, inter));
	else if (obj->type == cylinder)
		return (inter_cylinder(r, obj, inter));
	else if (obj->type == cone)
		return (inter_cone(r, obj, inter));
	else
		return (0);
}
