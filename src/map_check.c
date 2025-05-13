/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:26:13 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 17:16:21 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	check_position(char **map, int i, int j, int height)
{
	int	width;

	width = ft_strlen(map[i]);
	if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
		return (0);
	if (i > 0 && (map[i - 1][j] == ' '
		|| !is_valid_map_char(map[i - 1][j])))
		return (0);
	if (i < height - 1 && (map[i + 1][j] == ' '
		|| !is_valid_map_char(map[i + 1][j])))
		return (0);
	if (j > 0 && (map[i][j - 1] == ' ' || !is_valid_map_char(map[i][j - 1])))
		return (0);
	if (j < width - 1 && (map[i][j + 1] == ' '
		|| !is_valid_map_char(map[i][j + 1])))
		return (0);
	return (1);
}

static int	check_map_closed(char **map)
{
	int	i;
	int	j;
	int	height;

	height = array_len(map);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (is_space_or_player(map[i][j]))
			{
				if (!check_position(map, i, j, height))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	find_map_start(char **file, int *start)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == '1')
			{
				*start = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	find_map_section(char **file, int *start, int *end)
{
	if (!find_map_start(file, start))
		return (0);
	*end = *start;
	while (file[*end] && ft_strlen(file[*end]) > 0)
		(*end)++;
	return (1);
}

void	map_checker(char **file)
{
	int		map_start;
	int		map_end;
	int		map_height;
	char	**map;

	map_start = 0;
	map_end = 0;
	if (!find_map_section(file, &map_start, &map_end))
		ft_map_error("Map non trouvée\n");
	map = &file[map_start];
	map_height = map_end - map_start;
	if (!check_map_chars(map, map_height))
		ft_map_error("Caractère invalide dans la map\n");
	if (!check_map_closed(map))
		ft_map_error("La map n'est pas fermée\n");
}
