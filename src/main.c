/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:52:15 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 14:04:35 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main()
{
	t_env	env;
	
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, 1920, 1080, "Les blagues room");
	handle_hook(&env);
	mlx_loop(env.mlx);
	return (0);
}
