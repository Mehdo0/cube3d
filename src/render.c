/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:07:22 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 15:21:49 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	put_pixel(t_env *env, int x, int y, unsigned int color)
{
	char	*dst;

	dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_ceiling_floor(t_env *env)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = create_rgb(env->config->ceiling[0],
			env->config->ceiling[1], env->config->ceiling[2]);
	floor_color = create_rgb(env->config->floor[0],
			env->config->floor[1], env->config->floor[2]);
	render_ceiling(env, ceiling_color);
	render_floor(env, floor_color);
}

int	fps_counter(t_env *env)
{
	static int	prev_time = 0;
	static int	frames = 0;
	static int	fps = 0;
	int			time;
	char		fps_str[16];

	frames++;
	time = clock() / (CLOCKS_PER_SEC / 1000);
	if (time - prev_time >= 1000)
	{
		fps = frames;
		frames = 0;
		prev_time = time;
	}
	sprintf(fps_str, "FPS: %d", fps);
	mlx_string_put(env->mlx, env->win, 10, 20, 0xFFFFFF, fps_str);
	return (fps);
}

int	render_frame(t_env *env)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 0.04;
	rot_speed = 0.04;
	move_player(env, move_speed, rot_speed);
	env->img = mlx_new_image(env->mlx, SCREENWIDTH, SCREENHEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
			&env->line_length, &env->endian);
	render_ceiling_floor(env);
	cast_rays(env);
	draw_minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->img_textures->hud_img)
		draw_image_with_transparency(env, env->img_textures->hud_img,
			SCREENWIDTH - 170, 10);
	if (env->img_textures->rifle_img)
		draw_image_with_transparency(env, env->img_textures->rifle_img,
			SCREENWIDTH - 822, SCREENHEIGHT - 504);
	fps_counter(env);
	mlx_destroy_image(env->mlx, env->img);
	return (0);
}
