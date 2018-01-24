/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 13:10:17 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/24 10:25:40 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "vector_utility.h"
#include "intersection.h"

t_color		get_light_color(t_object *object, t_point inter, t_light *light)
{
	t_ray	light_vector;
	t_color	c;
	double	angle;

	light_vector = calc_vector(inter, light->pos);
	normalize_reversevector(&light_vector.pos);
	object->normal_vector = calc_vector(object->pos, inter);
	normalize_vector(&object->normal_vector.pos);
	angle = get_angle(light_vector.pos, object->normal_vector.pos);
	if (angle <= 0)
		c = (t_color){0, 0, 0, 1};
	else
	{
		c.r = (object->mater.diffuse.r * light->color.r * angle);
		c.g = (object->mater.diffuse.g * light->color.g * angle);
		c.b = (object->mater.diffuse.b * light->color.b * angle);
		printf("color = %f\n", c.r);
	}
	return (c);
}

t_ray       calc_vector(t_point a, t_point b)
{
	t_ray ab;

	ab.pos.x = b.x - a.x;
	ab.pos.y = b.y - a.y;
	ab.pos.z = b.z - a.z;
	return (ab);
}
