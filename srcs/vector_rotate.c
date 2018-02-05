/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:43:59 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/29 15:20:03 by ada-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_rotate.h"
#include <math.h>

void set_rotate(t_point rotate)
{
  rotate.x = 0;
  rotate.y = 0;
  rotate.z = 0;
}

static void rotate_x(t_point *vec, double angle)
{
	double	tmp_y;
	double	tmp_z;

	tmp_y = vec->y;
	tmp_z = vec->z;
	vec->y = tmp_y * cos(angle) + tmp_z * sin(angle);
	vec->z = -tmp_y * sin(angle) + tmp_z * cos(angle);
}

static void rotate_y(t_point *vec, double angle)
{
	double	tmp_x;
	double	tmp_z;

	tmp_x = vec->x;
	tmp_z = vec->z;
	vec->x = tmp_x * cos(angle) + tmp_z * sin(angle);
	vec->z = -tmp_x * sin(angle) + tmp_z * cos(angle);
}

static void rotate_z(t_point *vec, double angle)
{
    double  tmp_x;
    double  tmp_y;

    tmp_x = vec->x;
    tmp_y = vec->y;
    vec->x = tmp_x * cos(angle) + tmp_y * sin(angle);
    vec->y = -tmp_x * sin(angle) + tmp_y * cos(angle);
}

void rotate_vec(t_point *vec, t_point rotate)
{
  rotate_x(vec, ft_degtorad(rotate.x));
  rotate_y(vec, ft_degotrad(rotate.y));
  rotate_z(vec, ft_degtorad(rotate.z));
}
