/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:20:36 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 16:08:32 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_background(t_env *env, int start_x, int start_y,
			t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			put_pixel(env, start_x + x, start_y + y, 0x44000000);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_env *env, t_minimap_draw_params *params)
{
	int	tx;
	int	ty;

	ty = 0;
	while (ty < params->tile_size)
	{
		tx = 0;
		while (tx < params->tile_size)
		{
			if (is_valid_screen_pos(params->x + tx, params->y + ty))
				put_pixel(env, params->x + tx, params->y + ty, params->color);
			tx++;
		}
		ty++;
	}
}

void	draw_walls(t_env *env, int start_x, int start_y, int tile_size)
{
	t_minimap_draw_params	params;
	int				x;
	int				y;

	y = 0;
	while (y < env->config->map.height)
	{
		x = 0;
		while (x < env->config->map.width)
		{
			if (y < env->config->map.height && x < (int)ft_strlen(
					env->config->map.grid[y]))
			{
				params.color = get_tile_color(env->config->map.grid[y][x]);
				params.x = start_x + x * tile_size;
				params.y = start_y + y * tile_size;
				params.tile_size = tile_size;
				draw_tile(env, &params);
			}
			x++;
		}
		y++;
	}
}

static void	draw_player_circle(t_env *env, int px, int py)
{
	int	tx;
	int	ty;

	ty = -2;
	while (ty <= 2)
	{
		tx = -2;
		while (tx <= 2)
		{
			if (tx * tx + ty * ty <= 4)
				if (is_valid_screen_pos(px + tx, py + ty))
					put_pixel(env, px + tx, py + ty, 0xFFFFFF);
			tx++;
		}
		ty++;
	}
}

void	draw_player_direction(t_env *env, int px, int py, int size)
{
	t_player	*player;
	int			i;

	player = &env->config->player;
	draw_player_circle(env, px, py);
	i = 0;
	while (i < size)
	{
		if (is_valid_screen_pos(px + (int)(i * player->dirx / 2),
			py + (int)(i * player->diry / 2)))
			put_pixel(env, px + (int)(i * player->dirx / 2),
				py + (int)(i * player->diry / 2), 0xFF0000);
		i++;
	}
}
