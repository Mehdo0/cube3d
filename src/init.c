/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/18 14:58:12 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_config	*ft_init_config(void)
{
	t_config	*config;
    
    printf("DEBUG: Allocating config memory\n");
    config = malloc(sizeof(t_config));
    if (!config) {
        printf("DEBUG: Failed to allocate config\n");
        ft_map_error("Error\nMemory allocation failed\n");
    }
    printf("DEBUG: Initializing map\n");
	config->map = init_map();
	// Remove this condition - it's causing the error since grid is supposed to be NULL at init
	/*
	if (!config->map.grid)
	{
		ft_map_error("Error\nMemory allocation failed\n");
		printf("DEBUG: Map grid is NULL as expected after init_map\n");
	}
	*/
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

void initPlayer(t_player *player, t_map *map)
{
    for (int y = 0; y < map->height; y++)
	{
        for (int x = 0; x < map->width; x++)
		{
            char current = map->grid[y][x];
            if (current == 'N' || current == 'S' || current == 'E' || current == 'W')
			{
                player->posX = x + 0.5;
                player->posY = y + 0.5;
                if (current == 'N')
				{
                    player->dirX = 0;
                    player->dirY = -1;
                    player->planeX = 0.66;
                    player->planeY = 0;
                }
				else if (current == 'S')
				{
                    player->dirX = 0;
                    player->dirY = 1;
                    player->planeX = -0.66;
                    player->planeY = 0;
                }
				else if (current == 'W')
				{
                    player->dirX = -1;
                    player->dirY = 0;
                    player->planeX = 0;
                    player->planeY = -0.66;
                }
				else if (current == 'E')
				{
                    player->dirX = 1;
                    player->dirY = 0;
                    player->planeX = 0;
                    player->planeY = 0.66;
                }
                map->grid[y][x] = '0';
                return ;
            }
        }
    }
}

t_map init_map(void)
{
	t_map map;

	map.grid = NULL;
	map.width = 0;
	map.height = 0;
	return (map);
}

// void	load_textures(t_env *env)
// {
//     int	width;
//     int	height;

//     env->img_textures = malloc(sizeof(t_img));
//     if (!env->img_textures)
//         ft_map_error("Error\nMemory allocation failed\n");

//     printf("DEBUG: Loading texture: %s\n", env->config->no);
//     env->img_textures->wall_N = mlx_xpm_file_to_image(env->mlx, env->config->no, &width, &height);
//     printf("DEBUG: Loading texture: %s\n", env->config->so);
//     env->img_textures->wall_S = mlx_xpm_file_to_image(env->mlx, env->config->so, &width, &height);
//     printf("DEBUG: Loading texture: %s\n", env->config->ea);
//     env->img_textures->wall_E = mlx_xpm_file_to_image(env->mlx, env->config->ea, &width, &height);
//     printf("DEBUG: Loading texture: %s\n", env->config->we);
//     env->img_textures->wall_W = mlx_xpm_file_to_image(env->mlx, env->config->we, &width, &height);

//     if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
//         !env->img_textures->wall_E || !env->img_textures->wall_W)
//     {
//         ft_map_error("Error\nFailed to load textures\n");
//     }
// }

void	load_textures(t_env *env)
{
    int	width = 64;
    int	height = 64;
    int	color_N = 0xFF0000; // Rouge
    int	color_S = 0x00FF00; // Vert
    int	color_E = 0x0000FF; // Bleu
    int	color_W = 0xFFFF00; // Jaune

    env->img_textures = malloc(sizeof(t_img));
    if (!env->img_textures)
        ft_map_error("Error\nMemory allocation failed\n");

    // Créer des images unicolores
    env->img_textures->wall_N = mlx_new_image(env->mlx, width, height);
    env->img_textures->wall_S = mlx_new_image(env->mlx, width, height);
    env->img_textures->wall_E = mlx_new_image(env->mlx, width, height);
    env->img_textures->wall_W = mlx_new_image(env->mlx, width, height);

    // Remplir les images avec les couleurs
    int *data;
    int size = width * height;

    data = (int *)mlx_get_data_addr(env->img_textures->wall_N, &width, &height, &width);
    for (int i = 0; i < size; i++) data[i] = color_N;

    data = (int *)mlx_get_data_addr(env->img_textures->wall_S, &width, &height, &width);
    for (int i = 0; i < size; i++) data[i] = color_S;

    data = (int *)mlx_get_data_addr(env->img_textures->wall_E, &width, &height, &width);
    for (int i = 0; i < size; i++) data[i] = color_E;

    data = (int *)mlx_get_data_addr(env->img_textures->wall_W, &width, &height, &width);
    for (int i = 0; i < size; i++) data[i] = color_W;

    if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
        !env->img_textures->wall_E || !env->img_textures->wall_W)
    {
        ft_map_error("Error\nFailed to create color textures\n");
    }
}

void init_keys(t_keys *keys)
{
    keys->up = 0;
    keys->down = 0;
    keys->strafe_left = 0;
    keys->strafe_right = 0;
    keys->left = 0;
    keys->right = 0;
    keys->action = 0;
}