/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:19:01 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/31 13:56:45 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int ac, char **av)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	if (ac != 2)
		ft_map_error("Error\nInvalid number of arguments\n");
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, SCREENWIDTH, SCREENHEIGHT, "Cube3D");
	env.config = ft_init_and_parse_map(av[1]);
	init_keys(&env.keys);
	load_textures(&env);
	mlx_hook(env.win, 2, 1L << 0, key_press, &env);
	mlx_hook(env.win, 3, 1L << 1, key_release, &env);
	mlx_hook(env.win, 6, 1L << 6, mouse_move, &env);
	mlx_hook(env.win, 17, 0, close_window, &env);
	mlx_loop_hook(env.mlx, render_frame, &env);
	mlx_loop(env.mlx);
	return (0);
}
