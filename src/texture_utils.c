/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:19 by kgiraud          #+#    #+#             */
/*   Updated: 2025/05/13 15:31:19 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_tex_drawing(t_tex *tex_info, void *texture,
		int start, int end, int line_height, int *draw_start, int *draw_end)
{
	tex_info->data = mlx_get_data_addr(texture, &tex_info->bpp,
			&tex_info->line_len, &tex_info->endian);
	tex_info->step = (double)TEXHEIGHT / line_height;
	tex_info->pos = (start - SCREENHEIGHT / 2 + line_height / 2)
		* tex_info->step;
	if (*draw_start < 0)
	{
		tex_info->pos += (-(*draw_start)) * tex_info->step;
		*draw_start = 0;
	}
	if (*draw_end >= SCREENHEIGHT)
		*draw_end = SCREENHEIGHT - 1;
}

void	draw_textured_line(t_env *env, t_draw_line_params *params)
{
	int		y;
	int		tex_y;
	int		color;
	t_tex	tex_info;
	int		line_height;
	int		draw_start;
	int		draw_end;

	line_height = params->end - params->start;
	draw_start = params->start;
	draw_end = params->end - 1;
	init_tex_drawing(&tex_info, params->texture, params->start, params->end,
		line_height, &draw_start, &draw_end);
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_info.pos & (TEXHEIGHT - 1);
		tex_info.pos += tex_info.step;
		color = *(int *)(tex_info.data + tex_y * tex_info.line_len
				+ params->tex_x * (tex_info.bpp / 8));
		put_pixel(env, params->x, y, color);
		y++;
	}
}
