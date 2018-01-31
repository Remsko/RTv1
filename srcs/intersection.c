/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:51:28 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/31 13:50:49 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vector_utilities.h"
#include "math_utilities.h"

double   inter_cylinder(t_ray r, t_object *obj, double *t)
{
	t_point pos;
	t_point dir;
	t_point poly;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	poly.x = dir.x * dir.x + dir.y * dir.y;
	poly.y = dir.x * pos.x + dir.y * pos.y;
	poly.y *= 2.0;
	poly.z = pos.x * pos.x + pos.y * pos.y - obj->radius * obj->radius;
	return (solve_equation(poly, t));
}

double          inter_cone(t_ray r, t_object *obj, double *t)
{
	t_point pos;
	t_point dir;
	t_point poly;
	double	radius;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	radius = sin(ft_degtorad(obj->radius)) * sin(ft_degtorad(obj->radius));
	poly.x = dir.x * dir.x + dir.y * dir.y - dir.z * dir.z * radius;
	poly.y = dir.x * pos.x + dir.y * pos.y - dir.z * pos.z * radius;
	poly.y *= 2.0;
	poly.z = pos.x * pos.x + pos.y * pos.y - pos.z * pos.z * radius;
	return (solve_equation(poly, t));
}

double	inter_sphere(t_ray r, t_object *obj, double *t)
{
	t_point		dir;
	t_point		pos;
	t_point		poly;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	poly.x = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
	poly.y = dir.x * pos.x + dir.y * pos.y + dir.z * pos.z;
	poly.y *= 2.0;
	poly.z = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z;
	poly.z -= obj->radius * obj->radius;
	return (solve_equation(poly, t));
}

double	inter_plane(t_ray r, t_object *obj, double *t)
{
	double	n;
	double	d;
	t_point	dir;
	t_point	pos;
	t_point normal;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	normal = obj->normal;
	n = normal.x * pos.x + normal.y * pos.y + normal.z * pos.z;
	d = normal.x * dir.x + normal.y * dir.y + normal.z * dir.z;
	return (*t = -n / d > 0.000001 ? -n / d : MAX_RAY_LENGTH);
}

t_bool	intersection(t_ray r, t_object *obj, t_intersection *inter)
{
	double t;
	t_bool ret;

	t = MAX_RAY_LENGTH + 1000000;
	ret = 0;
	while (obj != NULL)
	{
		if (obj->type == sphere)
			inter_sphere(r, obj, &t);
		else if (obj->type == plan)
			inter_plane(r, obj, &t);
		else if (obj->type == cylinder)
			inter_cylinder(r, obj, &t);
		else if (obj->type == cone)
			inter_cone(r, obj, &t);
		if (t < inter->t && t > 0.000001)
		{
			inter->obj = obj;
			inter->t = t;
			ret = 1;
		}
		obj = obj->next;
	}
	return (ret);
}
