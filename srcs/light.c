/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 13:10:17 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/31 13:26:48 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "vector_utilities.h"
#include "intersection.h"
#include "math_utilities.h"
#include "obj_normal.h"

double           get_cos(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double			vector_norm(t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double			dot_production(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int				no_object_obstructing_light(t_light *light, t_intersection *inter, t_object *lst_obj)
{
	t_intersection	new_inter;
	t_ray			light_ray;
	double			light_distance;

	new_inter.t = MAX_RAY_LENGTH;
	light_ray.pos = inter->pos;
	light_ray.dir = vector_sub(light->pos, inter->pos);
	//	light_ray.dir = vector_sub(inter->pos, light->pos);
	light_distance = vector_norm(light_ray.dir);
	normalize_vector(&light_ray.dir);
	intersection(light_ray, lst_obj, &new_inter);
	if (new_inter.t > light_distance)
		return (1);
	return (0);
}

void		add_diffuse_light(t_color *c, t_object *obj, t_light *light, double cos)
{
	t_color light_intensity;

	light_intensity = (t_color){0.5, 0.5, 0.5, 1};
	c->r += cos * fmax(0, (obj->mater.diffuse.r / 255.0) * (light->color.r / 255.0) * (obj->color.r / 255.0) * light_intensity.r);
	c->g += cos * fmax(0, (obj->mater.diffuse.g / 255.0) * (light->color.g / 255.0) * (obj->color.g / 255.0) * light_intensity.g);
	c->b += cos * fmax(0, (obj->mater.diffuse.b / 255.0) * (light->color.b / 255.0) * (obj->color.b / 255.0) * light_intensity.b);
}

void		add_specular_light(t_color *c, t_point normal, t_point r_pos, t_point inter_pos, t_point light_vector, double cos_angle, t_object *obj)
{
	t_point refra;
	t_point vision;
	double	alpha;
	double	specular;
	t_point	tmp;
	double light_intensity;

	light_intensity = 0.8;
	(void)cos_angle;
	alpha = 100.0;
	tmp.x = 2.0 * dot_production(normal, light_vector) * normal.x;
	tmp.y = 2.0 * dot_production(normal, light_vector) * normal.y;
	tmp.z = 2.0 * dot_production(normal, light_vector) * normal.z;
	//	normalize_vector(&tmp);
	refra = vector_sub(tmp, light_vector);
	normalize_vector(&refra);
	vision = vector_sub(r_pos, inter_pos);
	normalize_vector(&vision);
	specular = pow(fmax(0, dot_product(refra, vision)), alpha);
	if (specular > 0)
	{
		c->r += specular * (obj->mater.specular.r / 255.0 * light_intensity);
		c->g += specular * (obj->mater.specular.g / 255.0 * light_intensity);
		c->b += specular * (obj->mater.specular.b / 255.0 * light_intensity);
	}
}

t_color		process_light(t_light *lst_light, t_object *lst_obj, t_intersection *inter, t_ray r)
{
	t_color c;
	t_color ambient;
	t_point	normal;
	t_point	light_vector;
	double	cos_angle;

	inter->pos.x = r.pos.x + r.dir.x * inter->t;
	inter->pos.y = r.pos.y + r.dir.y * inter->t;
	inter->pos.z = r.pos.z + r.dir.z * inter->t;
	// c = ambient_light();
	ambient = (t_color){0.5, 0.5, 0.5, 1};
	c = (t_color){ambient.r * (inter->obj->color.r / 255.0),
		ambient.g * (inter->obj->color.g / 255.0),
		ambient.b * (inter->obj->color.b / 255.0), 1};
	normal = (t_point){0.0, 0.0, 0.0};
	normal = get_normal(normal, inter);
	normalize_vector(&normal);
	while (lst_light)
	{
		if (no_object_obstructing_light(lst_light, inter, lst_obj))
		{
			light_vector = vector_sub(lst_light->pos, inter->pos);
			normalize_vector(&light_vector);
			cos_angle = dot_production(normal, light_vector);
			if (cos_angle >= 0.000001)
				add_diffuse_light(&c, inter->obj, lst_light, cos_angle);
			add_specular_light(&c, normal, r.pos, inter->pos, light_vector, cos_angle, inter->obj);
		}
		lst_light = lst_light->next;
	}
	return (c);
}
