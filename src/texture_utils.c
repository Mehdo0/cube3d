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
		t_tex_draw_params *params)
{
	tex_info->data = mlx_get_data_addr(texture, &tex_info->bpp,
			&tex_info->line_len, &tex_info->endian);
	tex_info->step = (double)TEXHEIGHT / params->line_height;
	tex_info->pos = (params->start - SCREENHEIGHT / 2 + params->line_height / 2)
		* tex_info->step;
	if (*(params->draw_start) < 0)
	{
		tex_info->pos += (-(*(params->draw_start))) * tex_info->step;
		*(params->draw_start) = 0;
	}
	if (*(params->draw_end) >= SCREENHEIGHT)
		*(params->draw_end) = SCREENHEIGHT - 1;
}

void	draw_textured_line(t_env *env, t_draw_line_params *params)
{
	t_tex				tex_info;
	t_tex_draw_params	draw_params;
	int					y;

	draw_params.line_height = params->end - params->start;
	draw_params.start = params->start;
	draw_params.end = params->end;
	draw_params.draw_start = &draw_params.start;
	draw_params.draw_end = &draw_params.end;
	draw_params.end--;
	init_tex_drawing(&tex_info, params->texture, &draw_params);
	y = draw_params.start;
	while (y <= draw_params.end)
	{
		put_pixel(env, params->x, y++,
			*(int *)(tex_info.data
				+ ((int)tex_info.pos & (TEXHEIGHT - 1)) * tex_info.line_len
				+ params->tex_x * (tex_info.bpp / 8)));
		tex_info.pos += tex_info.step;
	}
}
