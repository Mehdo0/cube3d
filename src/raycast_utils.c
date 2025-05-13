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
	wall->line_height = (int)(SCREENHEIGHT / wall->perp_wall_dist + 10);
	wall->draw_start = -wall->line_height / 2 + SCREENHEIGHT / 2;
	wall->draw_end = wall->line_height / 2 + SCREENHEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= SCREENHEIGHT)
		wall->draw_end = SCREENHEIGHT - 1;
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
	draw_textured_line(env, x, wall->draw_start, wall->draw_end,
		wall->texture, wall->tex_x, wall->line_height);
}

void draw_textured_line(t_env *env, int x, int drawStart, int drawEnd, 
						void *texture, int texX, int lineHeight)
{
	int		y;
	int		texY;
	int		color;
	double	step;
	double	texPos;
	char	*tex_data;
	int		tex_bpp;
	int		tex_line_length;
	int		tex_endian;

	tex_data = mlx_get_data_addr(texture, &tex_bpp, &tex_line_length, &tex_endian);
	step = 1.0 * TEXHEIGHT / lineHeight;
	texPos = (drawStart - SCREENHEIGHT / 2 + lineHeight / 2) * step;
	
	y = drawStart;
	while (y < drawEnd)
	{
		texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		color = *(int*)(tex_data + texY * tex_line_length + texX * (tex_bpp / 8));
		put_pixel(env, x, y, color);
		y++;
	}
}
