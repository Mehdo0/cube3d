/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:00:00 by kgiraud           #+#    #+#             */
/*   Updated: 2025/05/19 16:09:12 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	init_img_textures(t_env *env)
{
	int	width;
	int	height;

	check_texture_paths(env);
	load_wall_textures(env, &width, &height);
	if (!env->img_textures->wall_n || !env->img_textures->wall_s
		|| !env->img_textures->wall_e || !env->img_textures->wall_w)
		return (1);
	env->img_textures->hud_img = mlx_xpm_file_to_image(env->mlx,
			"textures/hud.xpm", &width, &height);
	env->img_textures->rifle_img = mlx_xpm_file_to_image(env->mlx,
			"textures/rifle.xpm", &width, &height);
	return (0);
}
