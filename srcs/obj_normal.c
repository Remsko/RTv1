/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:26:06 by rpinoit           #+#    #+#             */
/*   Updated: 2018/02/05 10:51:48 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_sphere_normal(t_intersection *inter)
{
	inter->normal = vector_sub(inter->pos, inter->obj.pos);
}

void	get_plane_normal(t_intersection *inter)
{
	inter->normal = inter->obj.normal;
}

void	get_cylinder_normal(t_intersection *inter)
{
	t_point rotate;

	rotate = (t_point){90, 120, 30};
	inter->normal = vector_sub(inter->pos, inter->obj.pos);
	rotate_vec(&inter->normal, rotate);
	inter->normal.z = 0;
	vec_unrotate(&inter->normal, rotate);
}

void	get_cone_normal(t_intersection *inter)
{
	inter->normal = vector_sub(inter->pos, inter->obj.pos);
	inter->normal.z *= -1;
}

void	get_normal(t_intersection *inter)
{
	t_object	obj;

	obj = inter->obj;
	if (obj.type == sphere)
		get_sphere_normal(inter);
	else if (obj.type == plan)
		get_plane_normal(inter);
	else if (obj.type == cylinder)
		get_cylinder_normal(inter);
	else if (obj.type == cone)
		get_cone_normal(inter);
}
