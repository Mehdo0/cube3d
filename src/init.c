/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/06/05 11:48:59 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_config	*ft_init_config(void)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		ft_map_error("Error\nMemory allocation failed\n");
	config->map = init_map();
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->floor[0] = 0;
	config->floor[1] = 0;
	config->floor[2] = 0;
	config->ceiling[0] = 0;
	config->ceiling[1] = 0;
	config->ceiling[2] = 0;
	return (config);
}

t_map	init_map(void)
{
	t_map	map;

	map.grid = NULL;
	map.width = 0;
	map.height = 0;
	return (map);
}

void	init_keys(t_keys *keys)
{
	keys->up = 0;
	keys->down = 0;
	keys->strafe_left = 0;
	keys->strafe_right = 0;
	keys->left = 0;
	keys->right = 0;
	keys->action = 0;
}

void	load_textures(t_env *env)
{
	env->img_textures = malloc(sizeof(t_img));
	if (!env->img_textures)
		ft_map_error("Error\nMemory allocation failed\n");
	if (init_img_textures(env) != 0)
	{
		printf("Failed to load textures from files, using color textures\n");
		ft_map_error("Error\n");
	}
	if (!env->img_textures->wall_n || !env->img_textures->wall_s
		|| !env->img_textures->wall_e || !env->img_textures->wall_w)
		ft_map_error("Error\nFailed to create textures\n");
}
