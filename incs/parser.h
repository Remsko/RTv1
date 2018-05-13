/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:32:01 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/03/08 18:31:35 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rtv1.h"

void	reader(t_env *env);

int		check_data_array(char **d, int size);

void	check_value(double value, double min, double max);

void	check_color(double r, double g, double b, double a);

void	init_object(t_env *env, t_list *lst, t_object_type type);

void	fill_object_struct(t_object *object, char **d, t_object_type type);

void	fill_light_struct(t_light *light, char **d);

void	get_cam_data(t_env *env, t_list *lst);

void	get_obj_data(t_env *env, t_list *lst);

void	get_light_data(t_env *env, t_list *lst);

void	fill_sphere_struct(t_object *object, char **d);

void	fill_cylinder_struct(t_object *object, char **d);

void	fill_cone_struct(t_object *object, char **d);

void	fill_plan_struct(t_object *object, char **d);

#endif
