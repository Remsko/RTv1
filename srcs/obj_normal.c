/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:26:06 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/31 18:34:00 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_sphere_normal(t_point *normal, t_intersection *inter)
{
	*normal = vector_sub(inter->pos, inter->obj.pos);
}

void	get_plane_normal(t_point *normal, t_intersection *inter)
{
	*normal = inter->obj.normal;
}

void	get_cylinder_normal(t_point *normal, t_intersection *inter)
{
	*normal = vector_sub(inter->pos, inter->obj.pos);
	normal->z = 0;
}

void	get_cone_normal(t_point *normal, t_intersection *inter)
{
	*normal = vector_sub(inter->pos, inter->obj.pos);
	normal->z *= -1;
}

void	get_normal(t_point *normal, t_intersection *inter)
{
	t_object	obj;

	obj = inter->obj;
	if (obj.type == sphere)
		get_sphere_normal(normal, inter);
	else if (obj.type == plan)
		get_plane_normal(normal, inter);
	else if (obj.type == cylinder)
		get_cylinder_normal(normal, inter);
	else if (obj.type == cone)
		get_cone_normal(normal, inter);
}
