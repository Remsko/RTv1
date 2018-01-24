/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:04:25 by nboste            #+#    #+#             */
/*   Updated: 2018/01/15 12:37:16 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

#include "rtv1.h"

void		raytracer_process(t_env *env);

t_ray		get_prim_ray(t_2ipair p, t_env *env);

t_color		raytrace(t_ray r, t_env *env);

t_color     process_light(t_env *env, t_point inter, t_color c, t_object *obj_ptr);

t_bool		check_object_between(t_point light_pos, t_point inter, t_object *obj);

#endif
