/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:41:34 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/29 20:11:42 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "rtv1.h"

t_color		process_light(t_light *lst_light, t_object *lst_obj, t_intersection *inter, t_ray r);

#endif
