/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:53:10 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/05/13 16:45:20 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		button_event(int button, int x, int y, t_env *e)
{
	(void)x;
	(void)y;
	if (button == M_LFT)
	{
		if (e->active_icon == 1 || e->active_icon == 2)
		{
			if (e->ambilight == 0)
				e->ambilight = 1;
			else
				e->ambilight = 0;
			e->mark = 1;
		}
		else if (e->active_icon == 3 || e->active_icon == 4)
		{
			if (e->shadow == 0)
				e->shadow = 1;
			else
				e->shadow = 0;
			e->mark = 1;
		}
	}
	return (0);
}

int		red_cross(void)
{
	exit(EXIT_SUCCESS);
}

int		loop_hook(t_env *env)
{
	if (env->mark == 1)
	{
		env->mark = 0;
		mlx_draw_rt(env);
	}
	return (0);
}
