/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:04:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/26 21:17:32 by mmouaffa         ###   ########.fr       */
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
	olddirx = env->config->player.dirX;
	env->config->player.dirX = env->config->player.dirX * cos
		(angle) - env->config->player.dirY * sin(angle);
	env->config->player.dirY = olddirx * sin
		(angle) + env->config->player.dirY * cos(angle);
	oldplanex = env->config->player.planeX;
	env->config->player.planeX = env->config->player.planeX * cos
		(angle) - env->config->player.planeY * sin(angle);
	env->config->player.planeY = oldplanex * sin
		(angle) + env->config->player.planeY * cos(angle);
	last_x = x;
	return (0);
}
