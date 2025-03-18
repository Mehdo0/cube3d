/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/18 22:05:19 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_config	*ft_init_config(void)
{
	t_config	*config;
    
    config = malloc(sizeof(t_config));
    if (!config) {
        ft_map_error("Error\nMemory allocation failed\n");
    }
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

void load_textures(t_env *env)
{
    // Allocate memory for texture structure
    env->img_textures = malloc(sizeof(t_img));
    if (!env->img_textures)
        ft_map_error("Error\nMemory allocation failed\n");
    
    // Try to load textures from XPM files
    if (init_img_textures(env) != 0)
    {
        // If loading fails, use color textures as fallback
        printf("Failed to load textures from files, using color textures instead\n");
        create_color_textures(env);
    }
    
    // Verify that all textures are available
    if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
        !env->img_textures->wall_E || !env->img_textures->wall_W)
    {
        ft_map_error("Error\nFailed to create textures\n");
    }
}

// Replace the init_img_textures function in parsing.c with this:
int init_img_textures(t_env *env)
{
    int width, height;
    
    // Make sure we have paths before attempting to load
    if (!env->config->no || !env->config->so || !env->config->ea || !env->config->we)
    {
        printf("Texture paths are missing\n");
        return (-1);
    }
    
    // Print paths for debugging
    printf("Loading textures from: %s, %s, %s, %s\n", 
           env->config->no, env->config->so, env->config->ea, env->config->we);
    
    // Load textures from XPM files
    env->img_textures->wall_N = mlx_xpm_file_to_image(env->mlx, env->config->no, &width, &height);
    env->img_textures->wall_S = mlx_xpm_file_to_image(env->mlx, env->config->so, &width, &height);
    env->img_textures->wall_E = mlx_xpm_file_to_image(env->mlx, env->config->ea, &width, &height);
    env->img_textures->wall_W = mlx_xpm_file_to_image(env->mlx, env->config->we, &width, &height);
    
    // Check if any texture failed to load
    if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
        !env->img_textures->wall_E || !env->img_textures->wall_W)
    {
        // Clean up any successfully loaded textures to avoid memory leaks
        if (env->img_textures->wall_N) mlx_destroy_image(env->mlx, env->img_textures->wall_N);
        if (env->img_textures->wall_S) mlx_destroy_image(env->mlx, env->img_textures->wall_S);
        if (env->img_textures->wall_E) mlx_destroy_image(env->mlx, env->img_textures->wall_E);
        if (env->img_textures->wall_W) mlx_destroy_image(env->mlx, env->img_textures->wall_W);
        
        return (-1);
    }
    
    return (0);
}

// Make sure create_color_textures properly initializes textures
void create_color_textures(t_env *env)
{
    int width = 64;
    int height = 64;
    int color_N = 0xFF0000; // Red
    int color_S = 0x00FF00; // Green
    int color_E = 0x0000FF; // Blue
    int color_W = 0xFFFF00; // Yellow
    
    // Create empty images
    env->img_textures->wall_N = mlx_new_image(env->mlx, width, height);
    env->img_textures->wall_S = mlx_new_image(env->mlx, width, height);
    env->img_textures->wall_E = mlx_new_image(env->mlx, width, height);
    env->img_textures->wall_W = mlx_new_image(env->mlx, width, height);
    
    // Verify image creation
    if (!env->img_textures->wall_N || !env->img_textures->wall_S || 
        !env->img_textures->wall_E || !env->img_textures->wall_W)
    {
        ft_map_error("Error\nFailed to create color textures\n");
    }
    
    // Fill images with colors
    int bpp, size_line, endian;
    int *data;
    
    data = (int *)mlx_get_data_addr(env->img_textures->wall_N, &bpp, &size_line, &endian);
    for (int i = 0; i < width * height; i++) data[i] = color_N;
    
    data = (int *)mlx_get_data_addr(env->img_textures->wall_S, &bpp, &size_line, &endian);
    for (int i = 0; i < width * height; i++) data[i] = color_S;
    
    data = (int *)mlx_get_data_addr(env->img_textures->wall_E, &bpp, &size_line, &endian);
    for (int i = 0; i < width * height; i++) data[i] = color_E;
    
    data = (int *)mlx_get_data_addr(env->img_textures->wall_W, &bpp, &size_line, &endian);
    for (int i = 0; i < width * height; i++) data[i] = color_W;
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
