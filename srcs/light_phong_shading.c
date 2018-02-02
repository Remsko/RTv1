/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_phong_shading.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:25:39 by rpinoit           #+#    #+#             */
/*   Updated: 2018/01/31 18:27:16 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void        set_ambient_light(t_color *c, t_object *obj)
{
	t_color ambient;

	ambient = (t_color){0.5, 0.5, 0.5, 1};
	*c = (t_color){ambient.r * (obj->color.r / 255.0), ambient.g * (obj->color.g / 255.0), ambient.b * (obj->color.b / 255.0), 1};
}
