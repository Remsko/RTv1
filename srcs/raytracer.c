/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:03:57 by nboste            #+#    #+#             */
/*   Updated: 2018/01/24 10:26:31 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "drawer.h"
#include <math.h>
#include "vector_utility.h"
#include "intersection.h"
#include "error.h"
#include "light.h"

void	raytracer_process(t_env *env)
{
	t_2ipair	i;
	t_ray		r;
	t_color		c;

	i.x = 0;
	while (i.x < env->rend.size.x)
	{
		i.y = 0;
		while (i.y < env->rend.size.y)
		{
			r = get_prim_ray(i, env);
			c = raytrace(r, env);
			drawer_putpixel(env, i, c);
			i.y++;
		}
		i.x++;
	}
}

t_ray	get_prim_ray(t_2ipair p, t_env *env)
{
	t_camera	*cam;
	t_ray		r;

	cam = &env->scene.cam;
	r.dir.x = cam->d * cam->uvn.n.x - (cam->near.x / 2) * cam->uvn.u.x + (cam->near.y / 2) * cam->uvn.v.x + (((double)p.x + 0.5) * cam->step.x) * cam->uvn.u.x - (((double)p.y + 0.5) * cam->step.y) * cam->uvn.v.x;
	r.dir.y = cam->d * cam->uvn.n.y - (cam->near.x / 2) * cam->uvn.u.y + (cam->near.y / 2) * cam->uvn.v.y + (((double)p.x + 0.5) * cam->step.x) * cam->uvn.u.y - (((double)p.y + 0.5) * cam->step.y) * cam->uvn.v.y;
	r.dir.z = cam->d * cam->uvn.n.z - (cam->near.x / 2) * cam->uvn.u.z + (cam->near.y / 2) * cam->uvn.v.z + (((double)p.x + 0.5) * cam->step.x) * cam->uvn.u.z - (((double)p.y + 0.5) * cam->step.y) * cam->uvn.v.z;
	normalize_vector(&r.dir);
	r.pos = cam->pos;
	r.depth = MAX_RAY_DEPTH;
	return (r);
}

t_color			raytrace(t_ray r, t_env *env)
{
	t_tmp		tmp;
	t_point		inter;
	t_color		color;
	t_object	*obj_ptr;
	double		dist;

	dist = 0xfffff;
	tmp.obj = env->scene.objs;
	obj_ptr = NULL;
	color = (t_color){0, 0, 0, 1};
	while (tmp.obj != NULL)
	{
		if (intersection(r, tmp.obj, &inter))
		{
			if (vec_dist(r.pos, inter) < dist)
			{
				dist = vec_dist(r.pos, inter);
				obj_ptr = tmp.obj;
				tmp.final_inter = inter;
			}
		}
		tmp.obj = tmp.obj->next;
	}
	if (obj_ptr != NULL)
		color = process_light(env, tmp.final_inter, color, obj_ptr);
	return (color);
}

t_color		process_light(t_env *env, t_point inter, t_color c, t_object *obj_ptr)
{
	t_tmp	tmp;
	int		i;
	double		r = 0;
	double		g = 0;
	double		b = 0;

	i = 0;
	tmp.light = env->scene.lgts;
	tmp.obj = env->scene.objs;
	while (tmp.light != NULL)
	{
		while (tmp.obj != NULL)
		{
			if (tmp.obj != obj_ptr)
			{
				if (check_object_between(tmp.light->pos, inter, tmp.obj))
				{
					i++;
					tmp.c = get_light_color(tmp.obj, inter, tmp.light);
					r += tmp.c.r;
					g += tmp.c.g;
					b += tmp.c.b;
				}
			}
			tmp.obj = tmp.obj->next;
		}
		tmp.light = tmp.light->next;
	}
	if (i)
		c = (t_color){(r * 255.0) > 255 ? 255 : (r * 255.0),
		   	(g * 255.0) > 255 ? 255 : (g * 255.0),
		   	(b * 255.0) > 255 ? 255 : (b * 255.0),
		   	1};
	else
		c = (t_color){0, 0, 0, 1};
	return (c);
}

t_bool		check_object_between(t_point light_pos, t_point inter, t_object *obj)
{
	t_tmp	tmp;

	tmp.shadow_ray = calc_vector(inter, light_pos);
	normalize_vector(&tmp.shadow_ray.pos);
	if (intersection(tmp.shadow_ray, obj, &tmp.final_inter))
	{
		if (calc_dist(inter, tmp.final_inter) > calc_dist(inter, tmp.light_pos))
			return (1);
	}
	return (0);
}
