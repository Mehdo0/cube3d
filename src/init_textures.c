/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/06/05 11:48:48 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	check_texture_paths(t_env *env)
{
	if (!env->config->no || !env->config->so
		|| !env->config->ea || !env->config->we)
		ft_map_error("Error\nMissing texture path in configuration\n");
}

void	load_wall_textures(t_env *env, int *width, int *height)
{
	env->img_textures->wall_n = mlx_xpm_file_to_image(env->mlx,
			env->config->no, width, height);
	env->img_textures->wall_s = mlx_xpm_file_to_image(env->mlx,
			env->config->so, width, height);
	env->img_textures->wall_e = mlx_xpm_file_to_image(env->mlx,
			env->config->ea, width, height);
	env->img_textures->wall_w = mlx_xpm_file_to_image(env->mlx,
			env->config->we, width, height);
}
