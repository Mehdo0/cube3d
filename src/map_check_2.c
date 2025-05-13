/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:26:13 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 17:16:28 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_check_borders(t_config *config)
{
	int	i;
	int	j;
	int	width;
	int	height;

	height = config->map.height;
	i = 0;
	while (i < height)
	{
		width = ft_strlen(config->map.grid[i]);
		j = 0;
		while (j < width)
		{
			if (is_space_or_player(config->map.grid[i][j]))
			{
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1
					|| !check_position(config->map.grid, i, j, height))
					ft_map_error("La map n'est pas fermée\n");
			}
			j++;
		}
		i++;
	}
}
