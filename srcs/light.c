/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 13:10:17 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/26 18:13:50 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "vector_utilities.h"
#include "intersection.h"
#include "math_utilities.h"

t_color		process_light(t_light *lst_light, t_object *lst_obj, t_object *obj_ptr, t_point inter)
{
	t_color c;
	//	t_color shadow;
	t_ray	light_ray;
	t_tmp	tmp;
	t_color ambient;

	ambient = (t_color){0.7, 0.7, 0.7, 1};
	//	shadow = (t_color){139, 139, 139, 1};
	c = (t_color){ambient.r * (obj_ptr->color.r / 255.0),
		ambient.g * (obj_ptr->color.g / 255.0),
		ambient.b * (obj_ptr->color.b / 255.0), 1};
	while (lst_light != NULL)
	{
		while (lst_obj != NULL)
		{
	//		if (obj_ptr != lst_obj)
	//		{
				light_ray.pos = lst_light->pos;
				light_ray.dir = vector_sub(inter, light_ray.pos);
				normalize_vector(&light_ray.dir);
				if (intersection(light_ray, lst_obj, &tmp.final_inter))
				{
					if (vec_dist(inter, light_ray.pos) < vec_dist(inter, tmp.final_inter))
					{
						tmp.c = get_light_color(obj_ptr, inter, lst_light);
						c.r += tmp.c.r;
						c.g += tmp.c.g;
						c.b += tmp.c.b;
					}
				}
	/*			else
				{
					tmp.c = get_light_color(obj_ptr, inter, lst_light);
					c.r += tmp.c.r;
					c.g += tmp.c.g;
					c.b += tmp.c.b;
				}*/ 
	//		}
			lst_obj = lst_obj->next;
		}
		lst_light = lst_light->next;
	}
	return (c);
}

t_color		get_light_color(t_object *object, t_point inter, t_light *light)
{
	t_ray	light_vector;
	t_color	c;
	double	angle;

	light_vector.pos = calc_vector(inter, light->pos);
	normalize_vector(&light_vector.pos);
	object->normal_vector.pos = calc_vector(object->pos, inter);
	normalize_vector(&object->normal_vector.pos);
	angle = get_angle(light_vector.pos, object->normal_vector.pos);
	if (angle <= 0)
		c = (t_color){0, 0, 0, 1};
	else
	{
		c.r = (object->mater.diffuse.r / 255.0) * (light->color.r / 255) * angle;
		c.g = (object->mater.diffuse.g / 255.0) * (light->color.g / 255) * angle;
		c.b = (object->mater.diffuse.b / 255.0) * (light->color.b / 255) * angle;
	}
	return (c);
}

t_point       calc_vector(t_point a, t_point b)
{
	t_point pos;

	pos.x = b.x - a.x;
	pos.y = b.y - a.y;
	pos.z = b.z - a.z;
	return (pos);
}
