/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:47:09 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/02/20 11:03:38 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void init_win(t_env *env, char *name)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->win_w, env->win_h, name);
}

int		main(int argc, char **argv)
{
	t_env	env;

	env.win_w = WIN_W;
	env.win_h = WIN_H;
	env.mark = 0;
	env.argc = argc;
	env.argv = argv;
	env.obj_rot = (t_point){0, 0, 0};
	env.cam_rot = (t_point){0, 0, 0};
	reader(&env);
	init_win(&env, argv[1]);
	mlx_expose_hook(env.win, expose_hook, &env);
	mlx_key_hook(env.win, key_hook, &env);
	//	init(&env);
	//	process(&env);
	//	destroy(&env);
	mlx_loop(env.mlx);
	return (0);
}
