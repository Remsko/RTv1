/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 13:10:17 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/31 18:58:39 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

int		intersection_is_light_position(t_point inter_pos, t_point light_pos)
{
	if ((int)inter_pos.x == (int)light_pos.x 
			&& (int)inter_pos.y == (int)light_pos.y 
			&& (int)inter_pos.z == (int)light_pos.z)
		return (1);
	return (0);
}

int				no_object_obstructing_light(t_light *light, t_intersection *inter, t_object *lst_obj)
{
	t_intersection	new_inter;
	t_ray			light_ray;
	double			light_distance;

	if (intersection_is_light_position(inter->pos, light->pos))
		return (0);
	new_inter.t = MAX_RAY_LENGTH;
	light_ray.pos = inter->pos;
	light_ray.dir = vector_sub(light->pos, inter->pos);
//		light_ray.dir = vector_sub(inter->pos, light->pos);
	light_distance = vector_norm(light_ray.dir);
	normalize_vector(&light_ray.dir);
	intersection(light_ray, lst_obj, &new_inter);
	if (new_inter.t <= light_distance)
		return (0);
	return (1);
}

void		add_diffuse_light(t_color *c, t_object obj, t_light *light, double cos)
{
	t_color light_intensity;

	light_intensity = (t_color){ .r = 0.5, .g = 0.5, .b = 0.5, .a = 1};
	c->r += cos * (obj.mater.diffuse.r / 255.0) * (light->color.r / 255.0) * (obj.color.r / 255.0) * light_intensity.r;
	c->g += cos * (obj.mater.diffuse.g / 255.0) * (light->color.g / 255.0) * (obj.color.g / 255.0) * light_intensity.g;
	c->b += cos * (obj.mater.diffuse.b / 255.0) * (light->color.b / 255.0) * (obj.color.b / 255.0) * light_intensity.b;
}

void		add_specular_light(t_color *c, t_point normal, t_point r_pos, t_point inter_pos, t_point light_vector, t_object obj)
{
	t_point refra;
	t_point vision;
	double	alpha;
	double	cos_omega;
	t_point	tmp;
	double light_intensity;

	light_intensity = 0.8;
	alpha = 100.0;
	tmp.x = 2.0 * dot_production(normal, light_vector) * normal.x;
	tmp.y = 2.0 * dot_production(normal, light_vector) * normal.y;
	tmp.z = 2.0 * dot_production(normal, light_vector) * normal.z;
	//	normalize_vector(&tmp);
	refra = vector_sub(tmp, light_vector);
	normalize_vector(&refra);
	vision = vector_sub(r_pos, inter_pos);
	normalize_vector(&vision);
	cos_omega = pow(fmax(0, dot_production(refra, vision)), alpha);
	if (cos_omega > 0)
	{
		c->r += cos_omega * (obj.mater.specular.r / 255.0 * light_intensity);
		c->g += cos_omega * (obj.mater.specular.g / 255.0 * light_intensity);
		c->b += cos_omega * (obj.mater.specular.b / 255.0 * light_intensity);
	}
}

void		set_ambient_light(t_color *c, t_color obj_color)
{
	t_color ambient;

	ambient = (t_color){0.5, 0.5, 0.5, 1};
	*c = (t_color){ambient.r * (obj_color.r / 255.0), ambient.g * (obj_color.g / 255.0), ambient.b * (obj_color.b / 255.0), 1};
}

t_color		process_light(t_light *lst_light, t_object *lst_obj, t_intersection *inter, t_ray r)
{
	t_color c;
	t_point	normal;
	t_point	light_vector;
	double	cos_teta;

	set_ambient_light(&c, inter->obj.color);
	get_normal(&normal, inter);
	normalize_vector(&normal);
	while (lst_light)
	{
		if (no_object_obstructing_light(lst_light, inter, lst_obj))
		{
			light_vector = vector_sub(lst_light->pos, inter->pos);
			normalize_vector(&light_vector);
			cos_teta = dot_production(normal, light_vector);
//			cos_teta = get_cos(normal, light_vector);
			if (cos_teta >= 0)
				add_diffuse_light(&c, inter->obj, lst_light, cos_teta);
			add_specular_light(&c, normal, r.pos, inter->pos, light_vector, inter->obj);
		}
		lst_light = lst_light->next;
	}
	return (c);
}
