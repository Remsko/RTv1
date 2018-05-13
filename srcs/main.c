/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:47:09 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/03/08 18:40:05 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

static void	init_win(t_env *env, char *name)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->win_w, env->win_h, name);
}

int			main(int argc, char **argv)
{
	t_env	env;

	env.win_w = WIN_W;
	env.win_h = WIN_H;
	env.mark = 0;
	env.argc = argc;
	env.argv = argv;
	reader(&env);
	env.init = 0;
	init_win(&env, argv[1]);
	env.mark = 1;
	env.ambilight = 0;
	env.shadow = 1;
	mlx_draw_rt(&env);
	mlx_hook(env.win, 6, 1L << 0, mouse_motion, &env);
	mlx_hook(env.win, 17, 1L << 17, red_cross, &env);
	mlx_hook(env.win, 2, 1L << 0, key_press, &env);
	mlx_hook(env.win, 4, 1L << 2, button_event, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
