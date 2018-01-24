/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utility.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 20:17:46 by nboste            #+#    #+#             */
/*   Updated: 2018/01/24 16:01:37 by ada-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILITY_H
# define VECTOR_UTILITY_H

#include "rtv1.h"

t_point vector_sub(t_point p1, t_point p2);

void	normalize_vector(t_point *p);

// double	get_norm(t_point p);

double	vect_len(t_point p);

double 	get_angle(t_point a, t_point b);

double  vec_dist(t_point p1, t_point p2);

#endif
