/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:51:28 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/03/08 18:44:38 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "math_utilities.h"
#include "vector_utilities.h"
#include "vector_rotate.h"

void	inter_cylinder(t_ray r, t_object *obj, double *t)
{
	t_point		pos;
	t_point		dir;
	t_point		poly;

	dir = (t_point){r.dir.x, r.dir.y, r.dir.z};
	pos = vector_sub(r.pos, obj->pos);
	rotate_vec(&pos, obj->rot);
	rotate_vec(&dir, obj->rot);
	poly.x = dir.x * dir.x + dir.z * dir.z;
	poly.y = 2.0 * (dir.x * pos.x + dir.z * pos.z);
	poly.z = pos.x * pos.x + pos.z * pos.z - obj->radius * obj->radius;
	return (solve_equation(poly, t));
}

void	inter_cone(t_ray r, t_object *obj, double *t)
{
	t_point		pos;
	t_point		dir;
	t_point		poly;

	dir = (t_point){r.dir.x, r.dir.y, r.dir.z};
	pos = vector_sub(r.pos, obj->pos);
	rotate_vec(&pos, obj->rot);
	rotate_vec(&dir, obj->rot);
	poly.x = dir.x * dir.x - dir.y * dir.y + dir.z * dir.z;
	poly.y = 2.0 * (pos.x * dir.x - pos.y * dir.y + pos.z * dir.z);
	poly.z = pos.x * pos.x - pos.y * pos.y + pos.z * pos.z;
	return (solve_equation(poly, t));
}

void	inter_sphere(t_ray r, t_object *obj, double *t)
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

void	inter_plane(t_ray r, t_object *obj, double *t)
{
	double		n;
	double		d;
	t_point		dir;
	t_point		pos;
	t_point		normal;

	dir = r.dir;
	pos = vector_sub(r.pos, obj->pos);
	normal = obj->normal;
	n = normal.x * pos.x + normal.y * pos.y + normal.z * pos.z;
	d = normal.x * dir.x + normal.y * dir.y + normal.z * dir.z;
	*t = -n / d > 0.000001 ? -n / d : MAX_RAY_LENGTH;
}

t_bool	intersection(t_ray r, t_object *obj,
					t_intersection *inter)
{
	double		t;
	t_bool		ret;

	t = MAX_RAY_LENGTH;
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
			inter->obj = *obj;
			inter->t = t;
			ret = 1;
		}
		obj = obj->next;
	}
	return (ret);
}
