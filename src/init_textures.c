/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/19 16:09:10 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_color_vars(int *w, int *h, int colors[4])
{
	*w = 64;
	*h = 64;
	colors[0] = 0xFF0000;
	colors[1] = 0x00FF00;
	colors[2] = 0x0000FF;
	colors[3] = 0xFFFF00;
}

static void	fill_texture(void *img, int color, int width, int height)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*data;

	data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	ft_memset(data, color, width * height * sizeof(int));
}

void	create_color_textures(t_env *env)
{
	int		width;
	int		height;
	int		colors[4];
	void	*textures[4];

	init_color_vars(&width, &height, colors);
	textures[0] = mlx_new_image(env->mlx, width, height);
	textures[1] = mlx_new_image(env->mlx, width, height);
	textures[2] = mlx_new_image(env->mlx, width, height);
	textures[3] = mlx_new_image(env->mlx, width, height);
	if (!textures[0] || !textures[1] || !textures[2] || !textures[3])
		ft_map_error("Error\nFailed to create color textures\n");
	env->img_textures->wall_n = textures[0];
	env->img_textures->wall_s = textures[1];
	env->img_textures->wall_e = textures[2];
	env->img_textures->wall_w = textures[3];
	fill_texture(textures[0], colors[0], width, height);
	fill_texture(textures[1], colors[1], width, height);
	fill_texture(textures[2], colors[2], width, height);
	fill_texture(textures[3], colors[3], width, height);
}

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
