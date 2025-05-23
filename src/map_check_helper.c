/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:02:28 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 15:52:03 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	is_wall(char c)
{
	return (c == '1');
}

int	is_space_or_player(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_map_char(char c)
{
	return (is_wall(c) || is_space_or_player(c) || c == ' ');
}

int	check_map_chars(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
