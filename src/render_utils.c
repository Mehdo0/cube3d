/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:21:02 by kgiraud           #+#    #+#             */
/*   Updated: 2025/05/13 15:21:22 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_image_with_transparency(t_env *env, void *img, int pos_x,
		int pos_y)
{
	t_img_data	data;

	data.img_data = mlx_get_data_addr(img, &data.bpp,
			&data.line_length, &data.endian);
	data.y = 0;
	while (data.y < 68)
	{
		data.x = 0;
		while (data.x < 120)
		{
			data.pixel = *(int *)(data.img_data + data.y * data.line_length
					+ data.x * (data.bpp / 8));
			if ((data.pixel & 0xFFFFFF) != 0x000000)
				if (pos_x + data.x >= 0 && pos_x + data.x < SCREENWIDTH
					&& pos_y + data.y >= 0 && pos_y + data.y < SCREENHEIGHT)
					put_pixel(env, pos_x + data.x, pos_y + data.y, data.pixel);
			data.x++;
		}
		data.y++;
	}
}

void	render_ceiling(t_env *env, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			put_pixel(env, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	render_floor(t_env *env, int floor_color)
{
	int	x;
	int	y;

	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			put_pixel(env, x, y, floor_color);
			x++;
		}
		y++;
	}
}
