/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utilities.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:26:21 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/29 10:07:24 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILITIES_H
# define MATH_UTILITIES_H

#include "rtv1.h"

double	get_delta(double a, double b, double c);

double	dot_product(t_point p1, t_point p2);

t_point	cross_product(t_point a, t_point b);

double  solve_equation(t_point poly, double *t);

#endif
