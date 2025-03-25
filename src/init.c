/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/25 16:47:27 by mmouaffa         ###   ########.fr       */
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

int	findPlayerPosition(t_map *map, int *x, int *y)
{
	char	current;

	*(y) = 0;
	while (*(y) < map->height)
	{
		*(x) = 0;
		while (*(x) < map->width)
		{
			current = map->grid[*(y)][*(x)];
			if (current == 'N' || current == 'S'
				|| current == 'E' || current == 'W')
				return (current);
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

static void	setPlayerDirection1(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0;
	}
	if (direction == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
}

static void	setPlayerDirection2(t_player *player, char direction)
{
	if (direction == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
	if (direction == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = 0.66;
	}
}

void	initPlayer(t_player *player, t_map *map)
{
	int		x;
	int		y;
	char	direction;

	direction = findPlayerPosition(map, &x, &y);
	if (!direction)
		return;
	player->posX = x + 0.5;
	player->posY = y + 0.5;
	map->grid[y][x] = '0';
	setPlayerDirection1(player, direction);
	setPlayerDirection2(player, direction);
}

t_map	init_map(void)
{
	t_map	map;

	map.grid = NULL;
	map.width = 0;
	map.height = 0;
	return (map);
}

void	load_textures(t_env *env)
{
	env->img_textures = malloc(sizeof(t_img));
	if (!env->img_textures)
		ft_map_error("Error\nMemory allocation failed\n");
	if (init_img_textures(env) != 0)
	{
		printf
		("Failed to load textures from files, using color textures instead\n");
		create_color_textures(env);
	}
	if (!env->img_textures->wall_N || !env->img_textures->wall_S ||
		!env->img_textures->wall_E || !env->img_textures->wall_W)
		ft_map_error("Error\nFailed to create textures\n");
}

int	init_img_textures(t_env *env)
{
	int	width;
	int	height;

	if (!env->config->no || !env->config->so || !env->config->ea || !env->config->we)
		ft_map_error("Error\nMissing texture path in configuration\n");
	env->img_textures->wall_N = mlx_xpm_file_to_image(env->mlx, env->config->no, &width, &height);
	env->img_textures->wall_S = mlx_xpm_file_to_image(env->mlx, env->config->so, &width, &height);
	env->img_textures->wall_E = mlx_xpm_file_to_image(env->mlx, env->config->ea, &width, &height);
	env->img_textures->wall_W = mlx_xpm_file_to_image(env->mlx, env->config->we, &width, &height);
	env->img_textures->hud_img = mlx_xpm_file_to_image(env->mlx, "textures/HUD.xpm", &width, &height);
	if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
		!env->img_textures->wall_E || !env->img_textures->wall_W
		|| !env->img_textures->hud_img)
	{
		if (env->img_textures->wall_N)
			mlx_destroy_image(env->mlx, env->img_textures->wall_N);
		if (env->img_textures->wall_S)
			mlx_destroy_image(env->mlx, env->img_textures->wall_S);
		if (env->img_textures->wall_E)
			mlx_destroy_image(env->mlx, env->img_textures->wall_E);
		if (env->img_textures->wall_W)
			mlx_destroy_image(env->mlx, env->img_textures->wall_W);
		if (env->img_textures->hud_img)
			mlx_destroy_image(env->mlx, env->img_textures->hud_img);
		return (-1);
	}
	return (0);
}

void	create_color_textures(t_env *env)
{
	int	width;
	int	height;
	int	color_N;
	int	color_S;
	int	color_E;
	int	color_W;
	int	*data;
	int	bpp;
	int	size_line;
	int	endian;

	width = 64;
	height = 64;
	color_N = 0xFF0000;
	color_S = 0x00FF00;
	color_E = 0x0000FF;
	color_W = 0xFFFF00;
	env->img_textures->wall_N = mlx_new_image(env->mlx, width, height);
	env->img_textures->wall_S = mlx_new_image(env->mlx, width, height);
	env->img_textures->wall_E = mlx_new_image(env->mlx, width, height);
	env->img_textures->wall_W = mlx_new_image(env->mlx, width, height);
	if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
		!env->img_textures->wall_E || !env->img_textures->wall_W)
		ft_map_error("Error\nFailed to create color textures\n");
	data = (int *)mlx_get_data_addr(env->img_textures->wall_N, &bpp, &size_line, &endian);
	ft_memset(data, color_N, width * height * sizeof(int));
	data = (int *)mlx_get_data_addr(env->img_textures->wall_S, &bpp, &size_line, &endian);
	ft_memset(data, color_S, width * height * sizeof(int));
	data = (int *)mlx_get_data_addr(env->img_textures->wall_E, &bpp, &size_line, &endian);
	ft_memset(data, color_E, width * height * sizeof(int));
	data = (int *)mlx_get_data_addr(env->img_textures->wall_W, &bpp, &size_line, &endian);
	ft_memset(data, color_W, width * height * sizeof(int));
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
