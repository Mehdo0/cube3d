/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:56:24 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 17:14:47 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	find_player_position(t_map *map, int *x, int *y)
{
	char	current;

	*y = 0;
	while (*y < map->height)
	{
		*x = 0;
		while (*x < map->width)
		{
			current = map->grid[*y][*x];
			if (current == 'N' || current == 'S'
				|| current == 'E' || current == 'W')
				return (current);
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

void	set_player_direction1(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dirx = 0;
		player->diry = -1;
		player->planex = 0.66;
		player->planey = 0;
	}
	if (direction == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
		player->planex = -0.66;
		player->planey = 0;
	}
}

void	set_player_direction2(t_player *player, char direction)
{
	if (direction == 'W')
	{
		player->dirx = -1;
		player->diry = 0;
		player->planex = 0;
		player->planey = -0.66;
	}
	if (direction == 'E')
	{
		player->dirx = 1;
		player->diry = 0;
		player->planex = 0;
		player->planey = 0.66;
	}
}

void	init_player(t_player *player, t_map *map)
{
	int		x;
	int		y;
	char	direction;

	direction = find_player_position(map, &x, &y);
	if (!direction)
		return ;
	player->posx = x + 0.5;
	player->posy = y + 0.5;
	map->grid[y][x] = '0';
	set_player_direction1(player, direction);
	set_player_direction2(player, direction);
}
