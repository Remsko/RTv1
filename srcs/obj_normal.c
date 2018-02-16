/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:26:06 by rpinoit           #+#    #+#             */
/*   Updated: 2018/02/16 14:10:26 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_sphere_normal(t_intersection *inter)
{
	inter->normal = vector_sub(inter->pos, inter->obj.pos);
	normalize_vector(&inter->normal);
}

void	get_plane_normal(t_intersection *inter)
{
	inter->normal = inter->obj.normal;
	normalize_vector(&inter->normal);
}

void	get_cylinder_normal(t_intersection *inter)
{
	t_point	normal;

	normal = vector_sub(inter->pos, inter->obj.pos);
	rotate_vec(&normal, inter->obj.rot);
	normal.y = 0;
	vec_unrotate(&normal, inter->obj.rot);
	inter->normal = normal;
	normalize_vector(&inter->normal);
}

void	get_cone_normal(t_intersection *inter)
{
	t_point	normal;

	normal = vector_sub(inter->pos, inter->obj.pos);
	rotate_vec(&normal, inter->obj.rot);
	normal.y *= -1;
	vec_unrotate(&normal, inter->obj.rot);
	inter->normal = normal;
	normalize_vector(&inter->normal);
}

void	get_normal(t_intersection *inter)
{
	t_object_type	type;

	type = inter->obj.type;
	if (type == sphere)
		get_sphere_normal(inter);
	else if (type == plan)
		get_plane_normal(inter);
	else if (type == cylinder)
		get_cylinder_normal(inter);
	else if (type == cone)
		get_cone_normal(inter);
}
