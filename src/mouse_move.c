/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:04:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 14:34:26 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	mouse_move(int x, int y, t_env *env)
{
	static int	last_x;
	int			dx;
	float		angle;
	float		olddirx;
	float		oldplanex;

	(void)y;
	if (last_x == -1)
		last_x = x;
	dx = x - last_x;
	if (dx == 0)
		return (0);
	angle = dx * 0.005;
	olddirx = env->config->player.dirx;
	env->config->player.dirx = env->config->player.dirx * cos
		(angle) - env->config->player.diry * sin(angle);
	env->config->player.diry = olddirx * sin
		(angle) + env->config->player.diry * cos(angle);
	oldplanex = env->config->player.planex;
	env->config->player.planex = env->config->player.planex * cos
		(angle) - env->config->player.planey * sin(angle);
	env->config->player.planey = oldplanex * sin
		(angle) + env->config->player.planey * cos(angle);
	last_x = x;
	return (0);
}
