/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:04:24 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/17 14:05:23 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int dites_oui_aux_hook(int key, t_env *env)
{
	(void)env;
	//printf("%d\n", key);
	if (key == 65307)
		exit(0);
	return (0);
}

int close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	handle_hook(t_env *env)
{
	mlx_key_hook(env->win, dites_oui_aux_hook, env);
	mlx_hook(env->win, 17, 0, close_window, NULL);
}