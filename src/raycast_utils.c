/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:19 by kgiraud          #+#    #+#             */
/*   Updated: 2025/05/13 15:31:19 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	calc_wall_data(t_wall *wall, t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		wall->perp_wall_dist = (ray->map_x - player->posx
				+ (1 - ray->step_x) / 2.0f) / ray->ray_dirx;
	else
		wall->perp_wall_dist = (ray->map_y - player->posy
				+ (1 - ray->step_y) / 2.0f) / ray->ray_diry;
	wall->line_height = (int)(SCREENHEIGHT / wall->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + SCREENHEIGHT / 2;
	wall->draw_end = wall->line_height / 2 + SCREENHEIGHT / 2;
}

void	select_texture(t_wall *wall, t_ray *ray, t_env *env)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			wall->texture = env->img_textures->wall_e;
		else
			wall->texture = env->img_textures->wall_w;
	}
	else
	{
		if (ray->step_y > 0)
			wall->texture = env->img_textures->wall_s;
		else
			wall->texture = env->img_textures->wall_n;
	}
}

void	calc_texture_x(t_wall *wall, t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		wall->wall_x = player->posy + wall->perp_wall_dist * ray->ray_diry;
	else
		wall->wall_x = player->posx + wall->perp_wall_dist * ray->ray_dirx;
	wall->wall_x -= floor(wall->wall_x);
	wall->tex_x = (int)(wall->wall_x * (float)TEXWIDTH);
	if ((ray->side == 0 && ray->ray_dirx > 0)
		|| (ray->side == 1 && ray->ray_diry < 0))
		wall->tex_x = TEXWIDTH - wall->tex_x - 1;
}

void	draw_wall_line(t_env *env, int x, t_wall *wall)
{
	t_draw_line_params	params;

	params.x = x;
	params.start = wall->draw_start;
	params.end = wall->draw_end;
	params.texture = wall->texture;
	params.tex_x = wall->tex_x;
	draw_textured_line(env, &params);
}

static void	init_tex_drawing(t_tex *tex_info, void *texture,
		int start, int end)
{
	tex_info->data = mlx_get_data_addr(texture, &tex_info->bpp,
			&tex_info->line_len, &tex_info->endian);
	tex_info->step = 1.0 * TEXHEIGHT / (end - start);
	tex_info->pos = (start - SCREENHEIGHT / 2 + (end - start) / 2)
		* tex_info->step;
}
