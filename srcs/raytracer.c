/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:47:44 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/02/16 18:00:18 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define ANTI 0

t_color		anti_alias_color(t_color c[17])
{
	t_color color;

	color.r = (c[0].r + c[1].r + c[2].r + c[3].r + c[4].r + c[5].r + c[6].r + c[7].r + c[8].r + c[9].r + c[10].r + c[11].r + c[12].r + c[13].r + c[14].r + c[15].r + c[16].r) / 16.0;
	color.g = (c[0].g + c[1].g + c[2].g + c[3].g + c[4].g + c[5].g + c[6].g + c[7].g + c[8].g + c[9].g + c[10].g + c[11].g + c[12].g + c[13].g + c[14].g + c[15].g + c[16].g) / 16.0;
	color.b = (c[0].b + c[1].b + c[2].b + c[3].b + c[4].b + c[5].b + c[6].b + c[7].b + c[8].b + c[9].b + c[10].b + c[11].b + c[12].b + c[13].b + c[14].b + c[15].b + c[16].b) / 16.0;

	return (color);
}

t_color		anti_aliasing_rt(t_point win_pos, t_env *env)
{
	t_color	c[17];
	t_point	pix;
	t_ray	r;
	t_point tmp;

	tmp = win_pos;
	pix.x = 0;
	while (pix.x < 4)
	{
		pix.y = 0;
		while (pix.y < 4)
		{
			tmp.x = win_pos.x + pix.x * 0.25;
			tmp.y = win_pos.y + pix.y * 0.25;
			r = get_prim_ray(tmp, env);
			c[(int)pix.x + (int)pix.y * 4] = raytrace(r, env);
			pix.y++;
		}
		pix.x++;
	}
//	tmp.x = win_pos.x + 0.5;
//	tmp.y = win_pos.x + 0.5;
//	r = get_prim_ray(tmp, env);
//	c[4] = raytrace(r, env);
	return (anti_alias_color(c));
}

void		raytracer_process(t_env *env)
{
	t_point		win_pos;
	t_ray		r;
	t_color		c;

	win_pos.x = 0;
	while (win_pos.x < env->win_w)
	{
		win_pos.y = 0;
		while (win_pos.y < env->win_h)
		{
			if (ANTI == 1)
				c = anti_aliasing_rt(win_pos, env);
			else
			{
				r = get_prim_ray(win_pos, env);
//				(t_ray){env->scene.cam.pos,(t_point){
//						win_pos.x - (env->rend.size.x / 2),
//						win_pos.y - (env->rend.size.y / 2),
//						0},
//					MAX_RAY_DEPTH
//				};
				c = raytrace(r, env);
			}
			put_pixel(env, &win_pos, c);
	//		drawer_putpixel(env, win_pos, c);
			win_pos.y++;
		}
		win_pos.x++;
	}
}

t_ray		get_prim_ray(t_point p, t_env *env)
{
	t_camera	*cam;
	t_ray		r;

	cam = &env->scene.cam;
	r.dir.x = p.x - (env->win_w / 2);
	r.dir.y = (env->win_h / 2) - p.y;
	r.dir.z = cam->d;
	normalize_vector(&r.dir);
	r.pos = cam->pos;
//	rotate_vec(&r.dir, env->cam_rot);
	r.depth = MAX_RAY_DEPTH;
	return (r);
}

t_color		raytrace(t_ray r, t_env *env)
{
	t_intersection	inter;
//	t_point			reflect;
	t_color			c;

	c = (t_color){ .r = 0.0, .g = 0.0, .b = 0.0, .a = 1};
	inter.t = MAX_RAY_LENGTH;
	if (intersection(env, r, env->scene.objs, &inter))
	{
	//	get_reflected_ray(&r.reflect);
	//	get_inter_pos(&inter.pos, &r.reflect);
		if (env->mark == 0)
		{
			printf("x = %f\n", inter.obj.rot.x);
			printf("y = %f\n", inter.obj.rot.y);
			printf("z = %f\n", inter.obj.rot.z);
			env->mark = 1;
		}
		inter.pos = vector_add(r.pos, vector_multiply(r.dir, inter.t)); //+ reflect * EPSILON;
		get_normal(&inter);
		c = process_light(env, env->scene.lgts, env->scene.objs, &inter, r);
		get_final_color(&c);
	}
	return (c);
}
