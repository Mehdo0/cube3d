/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:02:32 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 15:35:01 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_ray(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2.0f * x / (float)SCREENWIDTH - 1.0f;
	ray->ray_dirx = player->dirx + player->planex * ray->camera_x;
	ray->ray_diry = player->diry + player->planey * ray->camera_x;
	ray->map_x = (int)(player->posx);
	ray->map_y = (int)(player->posy);
	if (fabs(ray->ray_dirx) < 1e-8)
		ray->delta_distx = 1e30;
	else
		ray->delta_distx = fabs(1.0f / ray->ray_dirx);
	if (fabs(ray->ray_diry) < 1e-8)
		ray->delta_disty = 1e30;
	else
		ray->delta_disty = fabs(1.0f / ray->ray_diry);
}

void	calc_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (player->posx - ray->map_x) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1.0f - player->posx)
			* ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (player->posy - ray->map_y) * ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1.0f - player->posy)
			* ray->delta_disty;
	}
}

void	perform_dda(t_ray *ray, t_map *map)
{
	ray->hit = 0;
	ray->side = 0;
	while (!ray->hit)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= map->width
			|| ray->map_y >= map->height || map->grid[ray->map_y][ray->map_x]
			== '1')
			ray->hit = 1;
	}
}

void	cast_rays(t_env *env)
{
	t_player	*player;
	t_map		*map;
	t_ray		ray;
	t_wall		wall;
	int			x;

	player = &env->config->player;
	map = &env->config->map;
	x = 0;
	while (x < SCREENWIDTH)
	{
		init_ray(&ray, player, x);
		calc_step_and_side_dist(&ray, player);
		perform_dda(&ray, map);
		calc_wall_data(&wall, &ray, player);
		select_texture(&wall, &ray, env);
		calc_texture_x(&wall, &ray, player);
		draw_wall_line(env, x, &wall);
		x++;
	}
}

void	draw_vertical_line(t_env *env, t_line *line)
{
	int		y;
	char	*dst;

	y = line->start;
	while (y <= line->end)
	{
		dst = env->addr + (y * env->line_length + line->x
				* (env->bits_per_pixel / 8));
		*(unsigned int *)dst = line->color;
		y++;
	}
}
