/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 13:10:17 by rpinoit           #+#    #+#             */
/*   Updated: 2018/03/08 18:43:08 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "light.h"
#include "math_utilities.h"
#include "vector_utilities.h"
#include "intersection.h"

int			no_object_obstructing_light(t_light *light,
					t_intersection *inter, t_object *lst_obj)
{
	t_intersection	new_inter;
	t_ray			light_ray;
	double			light_distance;

	new_inter.t = MAX_RAY_LENGTH;
	light_ray.pos = inter->pos;
	light_ray.dir = vector_sub(light->pos, inter->pos);
	light_distance = vector_len(light_ray.dir);
	normalize_vector(&light_ray.dir);
	intersection(light_ray, lst_obj, &new_inter);
	if (new_inter.t < light_distance)
		return (0);
	return (1);
}

t_color		process_light(const t_env *env, t_intersection *inter, t_ray r)
{
	t_object	*lst_obj;
	t_light		*lst_light;
	t_color		c;
	double		cos_teta;

	lst_light = env->thenv[0]->scene.lgts;
	lst_obj = env->thenv[0]->scene.objs;
	set_ambient_light(&c, inter->obj);
	while (env->thenv[0]->ambilight == 0 && lst_light)
	{
		if (env->thenv[0]->shadow == 0
			|| no_object_obstructing_light(lst_light, inter, lst_obj))
		{
			inter->light_vector = vector_sub(lst_light->pos, inter->pos);
			normalize_vector(&inter->light_vector);
			cos_teta = dot_product(inter->normal, inter->light_vector);
			if (cos_teta >= 0 && cos_teta <= 1)
				add_diffuse_light(&c, inter->obj, lst_light, cos_teta);
			add_specular_light(&c, r.pos, inter);
		}
		lst_light = lst_light->next;
	}
	return (c);
}
