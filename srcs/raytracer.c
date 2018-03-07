/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:47:44 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/03/07 15:54:43 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		*raytracer_process(void *arg)
{
	t_point		win_pos;
	t_ray		r;
	t_color		c;
	t_env		*env;
	double		win_max;

	env = (t_env *)arg;
	win_pos.x = (env->thenv[0]->win_w / NBTHREAD) * env->i_th;
	win_max = (env->thenv[0]->win_w / NBTHREAD) * (env->i_th + 1);
	while (win_pos.x < win_max)
	{
		win_pos.y = 0;
		while (win_pos.y < env->thenv[0]->win_h)
		{
			if (ANTI == 1)
				c = anti_aliasing_rt(win_pos, env);
			else
			{
				r = get_prim_ray(win_pos, env);
				c = raytrace(r, env);
			}
			if (SEPIA == 1)
				sepia(&c);
			else if (FIFTYSHADES == 1)
				fifty_shades_of_grey(&c);
			else if (DALTO == 1)
				daltonism(&c);
			put_pixel(env, &win_pos, c);
			win_pos.y++;
		}
		win_pos.x++;
	}
	pthread_exit(NULL);
	return (NULL);
}

t_ray		get_prim_ray(const t_point p, const t_env *env)
{
	t_camera	*cam;
	t_ray		r;

	cam = &env->thenv[0]->scene.cam;
	r.dir.x = p.x - (env->thenv[0]->win_w / 2);
	r.dir.y = p.y - (env->thenv[0]->win_h / 2);
	r.dir.z = cam->d;
	normalize_vector(&r.dir);
	r.pos = cam->pos;
	rotate_vec(&r.dir, env->thenv[0]->cam_rot);
	normalize_vector(&r.dir);
	r.depth = 1;
	return (r);
}

void		get_reflected_ray(t_ray *reflected, t_intersection *inter, const t_ray *r)
{
	t_point	vision;

	vision = vector_sub(r->pos, inter->pos);
	reflected->pos = inter->pos;
	reflected->dir = vector_sub(vector_multiply(inter->normal,
				2.0 * dot_product(inter->normal,
					vision)), vision);
	reflected->depth = r->depth - 1;
	normalize_vector(&reflected->dir);
}

void		get_refracted_ray(t_ray *refracted, t_intersection *inter, const t_ray *r)
{
	t_point vision;

	vision = vector_sub(r->pos, inter->pos);
	refracted->pos = inter->pos;
	refracted->dir = vector_sub(vector_multiply(inter->normal,
				2.0 * dot_product(inter->normal,
					vision)), vision);
	refracted->depth = r->depth - 1;
	normalize_vector(&refracted->dir);
}

t_color		raytrace(t_ray r, const t_env *env)
{
	t_intersection	inter;
	t_color			c;
	t_color			r_c;
	t_ray			reflected_ray;
//	t_ray			refracted_ray;

	/*	t_object *tamer;

		tamer = (t_object*)malloc(sizeof(t_object));
		tamer->next = NULL;
		tamer->type = hyperboloid;
		tamer->pos.x = 0;
		tamer->pos.y = 0;
		tamer->pos.z = 2000;
		tamer->pos = (t_point){ .x = 0, .y = 0, .z = 200};
	//  tamer->mater.specular = (t_color){ .r = 255, .g = 255, .b = 255, .a = 1};
	tamer->mater.ambient = (t_color){ .r = 255, .g = 0, .b = 0, .a = 1};
	//	tamer->mater.diffuse = (t_color){ .r = 255, .g = 255, .b = 255, .a = 1};
	env->scene.objs = tamer;
	*/
	c = (t_color){ .r = 0.0, .g = 0.0, .b = 0.0, .a = 1};
	inter.t = MAX_RAY_LENGTH;
	if (intersection(env, r, env->thenv[0]->scene.objs, &inter))
	{
		inter.pos = vector_add(r.pos, vector_multiply(r.dir, inter.t)); //+ reflect * EPSILON;
		inter.normal = get_normal(&inter);
		c = process_light(env, env->thenv[0]->scene.lgts, env->thenv[0]->scene.objs, &inter, r);
		get_final_color(&c);
		if (inter.obj.type == sphere)
			inter.obj.reflection = 1;
		else
			inter.obj.reflection = 0;
		//		if (inter.obj.type == plan)
		//		{
		//			printf("r.depth = %d\n", r.depth);
		//			exit(-1);
		//		}
		if (inter.obj.reflection > 0 && r.depth > 0)
		{
			get_reflected_ray(&reflected_ray, &inter, &r);
			r_c = raytrace(reflected_ray, env);
			c.r *= (1 - inter.obj.reflection);
			c.g *= (1 - inter.obj.reflection);
			c.b *= (1 - inter.obj.reflection);
			if (r_c.r != 0.0 && r_c.r != 0.0 && r_c.r != 0.0)
			{
				c.r += inter.obj.reflection * r_c.r;
				c.g += inter.obj.reflection * r_c.g;
				c.b += inter.obj.reflection * r_c.b;
			}
		}
	/*	if (inter.obj.refraction > 0 && r.depth > 0)
		{
			get_refracted_ray(&refracted_ray, &inter, &r);
			r_c = raytrace(refracted_ray, env);
			c.r *= (1 - inter.obj.refraction);
			c.g *= (1 - inter.obj.refraction);
			c.b *= (1 - inter.obj.refraction);
			if (r_c.r != 0.0 && r_c.r != 0.0 && r_c.r != 0.0)
			{
				c.r += inter.obj.refraction * r_c.r;
				c.g += inter.obj.refraction * r_c.g;
				c.b += inter.obj.refraction * r_c.b;
			}
		}*/
	}
	return (c);
}
