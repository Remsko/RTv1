/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:31:49 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/26 17:32:17 by ada-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rtv1.h"

static t_point norm_sphere(t_point *pos, t_object *o)
{
	t_point norm;

	norm = vector_sub(*pos, obj->pos);
	normalize_vector(&norm);
	return (norm);
}

static t_point norm_cone(t_point *pos, t_object *o)
{
	t_point norm;

	norm = vector_sub(*pos, obj->pos);
	normal.y *= -1;
	normalize_vector(&norm);
	return (norm);
}

static t_point norm_cylinder(t_point *pos, t_object *o)
{
	t_point norm;

	norm = vector_sub(*pos, obj->pos);
	normal.y = 0;
	normalize_vector(&norm);
	return (norm);
}

/*
static t_point norm_plan(t_point *pos, t_object *o)
{
	t_point norm;

	norm = vector_sub(*pos, obj->pos);
	
}
*/

t_point get_normal(t_point *pos, t_object *o)
{
	if (obj->type == sphere)
		return (norm_sphere(pos, obj));
//	else if (obj->type == plan)
	//	return (norm_plan(pos, obj));
	else if (obj->type == cylinder)
		return (norm_cylinder(pos, obj));
	else if (obj->type == cone)
		return (norm_cone(pos, obj));
	return ((t_point){0, 0, 0});
}
