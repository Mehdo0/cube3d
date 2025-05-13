/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:08:35 by kgiraud           #+#    #+#             */
/*   Updated: 2025/05/13 16:08:54 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	draw_border(t_env *env, t_minimap *map)
{
	int	i;

	i = map->start_x - 1;
	while (i <= map->start_x + map->width)
	{
		put_pixel(env, i, map->start_y - 1, 0xFFFFFF);
		put_pixel(env, i, map->start_y + map->height, 0xFFFFFF);
		i++;
	}
	i = map->start_y - 1;
	while (i <= map->start_y + map->height)
	{
		put_pixel(env, map->start_x - 1, i, 0xFFFFFF);
		put_pixel(env, map->start_x + map->width, i, 0xFFFFFF);
		i++;
	}
}

void	draw_minimap(t_env *env)
{
	t_minimap	map;
	int			player_x;
	int			player_y;

	map.tile_size = 10;
	map.width = env->config->map.width * map.tile_size;
	map.height = env->config->map.height * map.tile_size;
	map.start_x = 50;
	map.start_y = SCREENHEIGHT - map.height - 50;
	draw_background(env, map.start_x, map.start_y, &map);
	draw_walls(env, map.start_x, map.start_y, map.tile_size);
	player_x = map.start_x + (int)(env->config->player.posx * map.tile_size);
	player_y = map.start_y + (int)(env->config->player.posy * map.tile_size);
	draw_player_direction(env, player_x, player_y, map.tile_size * 2);
	draw_border(env, &map);
}

int is_valid_screen_pos(int x, int y)
{
	return (x >= 0 && x < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT);
}

int get_tile_color(char tile)
{
	if (tile == '1')
		return (0xFFFFFF);  // Mur blanc
	else if (tile == '0')
		return (0x44000000);  // Espace transparent
	else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0x44FF0000);  // Position du joueur en rouge transparent
	else
		return (0x44000000);  // Par défaut, transparent
}
