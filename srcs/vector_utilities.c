/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 10:30:57 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/31 17:27:56 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normalize_vector(t_point *p)
{
	double	len;

	len = sqrt((p->x * p->x) + (p->y * p->y) + (p->z * p->z));
	if (len > 0)
	{
		p->x = p->x / len;
		p->y = p->y / len;
		p->z = p->z / len;
	}
}

t_point	vector_sub(t_point p1, t_point p2)
{
	t_point	p;

	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return (p);
}
