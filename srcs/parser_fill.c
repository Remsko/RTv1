/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:13:19 by rpinoit           #+#    #+#             */
/*   Updated: 2018/03/09 14:08:39 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"
#include "vector_utilities.h"

void	fill_sphere_struct(t_object *object, char **d)
{
	object->radius = ft_atod(d[4]);
	object->color = (t_color){ft_atod(d[5]), ft_atod(d[6]),
		ft_atod(d[7]), ft_atod(d[8])};
	check_color(ft_atod(d[9]), ft_atod(d[10]), ft_atod(d[11]), ft_atod(d[12]));
	object->mater.specular = (t_color){ft_atod(d[9]), ft_atod(d[10]),
		ft_atod(d[11]), ft_atod(d[12])};
	check_color(ft_atod(d[13]), ft_atod(d[14]), ft_atod(d[15]), ft_atod(d[16]));
	object->mater.ambient = (t_color){ft_atod(d[13]), ft_atod(d[14]),
		ft_atod(d[15]), ft_atod(d[16])};
	check_color(ft_atod(d[17]), ft_atod(d[18]), ft_atod(d[19]), ft_atod(d[20]));
	object->mater.diffuse = (t_color){ft_atod(d[17]), ft_atod(d[18]),
		ft_atod(d[19]), ft_atod(d[20])};
}

void	fill_plan_struct(t_object *object, char **d)
{
	object->normal = (t_point){ft_atod(d[4]), ft_atod(d[5]), ft_atod(d[6])};
	normalize_vector(&object->normal);
	check_color(ft_atod(d[7]), ft_atod(d[8]), ft_atod(d[9]), ft_atod(d[10]));
	object->color = (t_color){ft_atod(d[7]), ft_atod(d[8]),
		ft_atod(d[9]), ft_atod(d[10])};
	check_color(ft_atod(d[11]), ft_atod(d[12]), ft_atod(d[13]), ft_atod(d[14]));
	object->mater.specular = (t_color){ft_atod(d[11]), ft_atod(d[12]),
		ft_atod(d[13]), ft_atod(d[14])};
	check_color(ft_atod(d[15]), ft_atod(d[16]), ft_atod(d[17]), ft_atod(d[18]));
	object->mater.ambient = (t_color){ft_atod(d[15]), ft_atod(d[16]),
		ft_atod(d[17]), ft_atod(d[18])};
	check_color(ft_atod(d[19]), ft_atod(d[20]), ft_atod(d[21]), ft_atod(d[22]));
	object->mater.diffuse = (t_color){ft_atod(d[19]), ft_atod(d[20]),
		ft_atod(d[21]), ft_atod(d[22])};
}

void	fill_cone_struct(t_object *object, char **d)
{
	object->radius = ft_atod(d[4]);
	object->rot = (t_point){ft_atod(d[5]), ft_atod(d[6]), ft_atod(d[7])};
	check_value(object->rot.x, -360, 360);
	check_value(object->rot.y, -360, 360);
	check_value(object->rot.z, -360, 360);
	check_color(ft_atod(d[8]), ft_atod(d[9]), ft_atod(d[10]), ft_atod(d[11]));
	object->color = (t_color){ft_atod(d[8]), ft_atod(d[9]),
		ft_atod(d[10]), ft_atod(d[11])};
	check_color(ft_atod(d[12]), ft_atod(d[13]), ft_atod(d[14]), ft_atod(d[15]));
	object->mater.specular = (t_color){ft_atod(d[12]), ft_atod(d[13]),
		ft_atod(d[14]), ft_atod(d[15])};
	check_color(ft_atod(d[16]), ft_atod(d[17]), ft_atod(d[18]), ft_atod(d[19]));
	object->mater.ambient = (t_color){ft_atod(d[16]), ft_atod(d[17]),
		ft_atod(d[18]), ft_atod(d[19])};
	check_color(ft_atod(d[20]), ft_atod(d[21]), ft_atod(d[22]), ft_atod(d[23]));
	object->mater.diffuse = (t_color){ft_atod(d[20]), ft_atod(d[21]),
		ft_atod(d[22]), ft_atod(d[23])};
}

void	fill_cylinder_struct(t_object *object, char **d)
{
	object->radius = ft_atod(d[4]);
	object->rot = (t_point){ft_atod(d[5]), ft_atod(d[6]), ft_atod(d[7])};
	check_value(object->rot.x, -360, 360);
	check_value(object->rot.y, -360, 360);
	check_value(object->rot.z, -360, 360);
	check_color(ft_atod(d[8]), ft_atod(d[9]), ft_atod(d[10]), ft_atod(d[11]));
	object->color = (t_color){ft_atod(d[8]), ft_atod(d[9]),
		ft_atod(d[10]), ft_atod(d[11])};
	check_color(ft_atod(d[12]), ft_atod(d[13]), ft_atod(d[14]), ft_atod(d[15]));
	object->mater.specular = (t_color){ft_atod(d[12]), ft_atod(d[13]),
		ft_atod(d[14]), ft_atod(d[15])};
	check_color(ft_atod(d[16]), ft_atod(d[17]), ft_atod(d[18]), ft_atod(d[19]));
	object->mater.ambient = (t_color){ft_atod(d[16]), ft_atod(d[17]),
		ft_atod(d[18]), ft_atod(d[19])};
	check_color(ft_atod(d[20]), ft_atod(d[21]), ft_atod(d[22]), ft_atod(d[23]));
	object->mater.diffuse = (t_color){ft_atod(d[20]), ft_atod(d[21]),
		ft_atod(d[22]), ft_atod(d[23])};
}
