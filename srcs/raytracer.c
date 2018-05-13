/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:47:44 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/03/09 14:02:18 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "light.h"
#include "raytracer.h"
#include "obj_normal.h"
#include "vector_utilities.h"
#include "intersection.h"
#include "pixel.h"
#include "vector_rotate.h"

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
			{
				r = get_prim_ray(win_pos, env);
				c = raytrace(r, env);
			}
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
	rotate_vec(&r.dir, cam->rot);
	normalize_vector(&r.dir);
	r.depth = MAX_RAY_DEPTH;
	return (r);
}

t_color		raytrace(const t_ray r, const t_env *env)
{
	t_intersection	inter;
	t_color			c;

	c = (t_color){ .r = 0.0, .g = 0.0, .b = 0.0, .a = 1};
	inter.t = MAX_RAY_LENGTH;
	if (intersection(r, env->thenv[0]->scene.objs, &inter))
	{
		inter.pos = vector_add(r.pos, vector_multiply(r.dir, inter.t));
		inter.normal = get_normal(&inter);
		c = process_light(env, &inter, r);
		get_final_color(&c);
	}
	return (c);
}
