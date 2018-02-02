/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utilities.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:26:47 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/02/02 12:32:38 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILITIES_H
# define VECTOR_UTILITIES_H

# include "rtv1.h"

double	vector_norm(t_point a);

double	dot_product(t_point a, t_point b);

t_point	vector_multiply(t_point vec, double factor);

void	normalize_vector(t_point *p);

t_point	vector_sub(t_point p1, t_point p2);

#endif
