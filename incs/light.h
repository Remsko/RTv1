/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:41:34 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/03/08 18:12:22 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "rtv1.h"

void		set_ambient_light(t_color *c, t_object obj);

void		add_diffuse_light(t_color *c, t_object obj, t_light *light,
						double cos_teta);

void		add_specular_light(t_color *c, t_point r_pos,
						t_intersection *inter);

t_color		process_light(const t_env *env, t_intersection *inter, t_ray r);

#endif
