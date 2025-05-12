/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 14:33:24 by mmouaffa         ###   ########.fr       */
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
		player->dirx = 0;
		player->diry = -1;
		player->planex = 0.66;
		player->planey = 0;
	}
	if (direction == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
		player->planex = -0.66;
		player->planey = 0;
	}
}

static void	setPlayerDirection2(t_player *player, char direction)
{
	if (direction == 'W')
	{
		player->dirx = -1;
		player->diry = 0;
		player->planex = 0;
		player->planey = -0.66;
	}
	if (direction == 'E')
	{
		player->dirx = 1;
		player->diry = 0;
		player->planex = 0;
		player->planey = 0.66;
	}
}

void	initPlayer(t_player *player, t_map *map)
{
	int		x;
	int		y;
	char	direction;

	direction = findPlayerPosition(map, &x, &y);
	if (!direction)
		return ;
	player->posx = x + 0.5;
	player->posy = y + 0.5;
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
	if (!env->img_textures->wall_n || !env->img_textures->wall_s ||
		!env->img_textures->wall_e || !env->img_textures->wall_w)
		ft_map_error("Error\nFailed to create textures\n");
}

int	init_img_textures(t_env *env)
{
	int width;
	int height;

	// Vérification que tous les chemins de texture essentiels sont présents.
	if (!env->config->no || !env->config->so || !env->config->ea ||
		!env->config->we)
		ft_map_error("Error\nMissing texture path in configuration\n");

	// Charger les textures à partir des fichiers XPM
	env->img_textures->wall_n = mlx_xpm_file_to_image(env->mlx, env->config->no, &width, &height);
	env->img_textures->wall_s = mlx_xpm_file_to_image(env->mlx, env->config->so, &width, &height);
	env->img_textures->wall_e = mlx_xpm_file_to_image(env->mlx, env->config->ea, &width, &height);
	env->img_textures->wall_w = mlx_xpm_file_to_image(env->mlx, env->config->we, &width, &height);
	env->img_textures->hud_img   = mlx_xpm_file_to_image(env->mlx, "textures/HUD.xpm", &width, &height);
	env->img_textures->rifle_img = mlx_xpm_file_to_image(env->mlx, "textures/rifle.xpm", &width, &height);

	// Vérifier que toutes les textures ont été chargées correctement.
	if (!env->img_textures->wall_n || !env->img_textures->wall_s || 
		!env->img_textures->wall_e || !env->img_textures->wall_w ||
		!env->img_textures->hud_img   || !env->img_textures->rifle_img)
	{
		if (env->img_textures->wall_n)
			mlx_destroy_image(env->mlx, env->img_textures->wall_n);
		if (env->img_textures->wall_s)
			mlx_destroy_image(env->mlx, env->img_textures->wall_s);
		if (env->img_textures->wall_e)
			mlx_destroy_image(env->mlx, env->img_textures->wall_e);
		if (env->img_textures->wall_w)
			mlx_destroy_image(env->mlx, env->img_textures->wall_w);
		if (env->img_textures->hud_img)
			mlx_destroy_image(env->mlx, env->img_textures->hud_img);
		if (env->img_textures->rifle_img)
			mlx_destroy_image(env->mlx, env->img_textures->rifle_img);
		env->img_textures->wall_n = NULL;
		env->img_textures->wall_s = NULL;
		env->img_textures->wall_w = NULL;
		env->img_textures->wall_e = NULL;
		env->img_textures->rifle_img = NULL;
		env->img_textures->hud_img = NULL;
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
	env->img_textures->wall_n = mlx_new_image(env->mlx, width, height);
	env->img_textures->wall_s = mlx_new_image(env->mlx, width, height);
	env->img_textures->wall_e = mlx_new_image(env->mlx, width, height);
	env->img_textures->wall_w = mlx_new_image(env->mlx, width, height);
	if (!env->img_textures->wall_n || !env->img_textures->wall_s || 
		!env->img_textures->wall_e || !env->img_textures->wall_w)
		ft_map_error("Error\nFailed to create color textures\n");
	data = (int *)mlx_get_data_addr(env->img_textures->wall_n, &bpp, &size_line, &endian);
	ft_memset(data, color_N, width * height * sizeof(int));
	data = (int *)mlx_get_data_addr(env->img_textures->wall_s, &bpp, &size_line, &endian);
	ft_memset(data, color_S, width * height * sizeof(int));
	data = (int *)mlx_get_data_addr(env->img_textures->wall_e, &bpp, &size_line, &endian);
	ft_memset(data, color_E, width * height * sizeof(int));
	data = (int *)mlx_get_data_addr(env->img_textures->wall_w, &bpp, &size_line, &endian);
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
