/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:45:40 by mmouaffa          #+#    #+#             */
/*   Updated: 2024/11/04 14:16:47 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_copy_on_error(char **copy, int i)
{
	while (--i >= 0)
		free(copy[i]);
	free(copy);
}

char	**ft_copy_map(char **map, int rows)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(rows * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_copy_on_error(copy, i);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	find_path(int x, int y, char **map)
{
	if (x < 0 || y < 0 || !map[y] || map[y][x] == '\0' ||
		map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == 'E')
		return (1);
	map[y][x] = 'V';
	if (find_path(x + 1, y, map)
		|| find_path(x - 1, y, map)
		|| find_path(x, y + 1, map)
		|| find_path(x, y - 1, map))
		return (1);
	return (0);
}

void	ft_locate_player(t_data *data)
{
	data->map->y = 0;
	while (data->map->y < (data->size_y / IMG_H))
	{
		data->map->x = 0;
		while (data->map->x < (data->size_x / IMG_W))
		{
			if (data->map->map[data->map->y][data->map->x] == 'P')
			{
				data->p_x = data->map->x;
				data->p_y = data->map->y;
				return ;
			}
			data->map->x++;
		}
		data->map->y++;
	}
}

void	ft_check_valid_path(t_data *data)
{
	char	**map_copy;
	int		is_path;
	int		rows;
	int		i;

	rows = data->size_y / IMG_H;
	ft_locate_player(data);
	map_copy = ft_copy_map(data->map->map, rows);
	if (!map_copy)
		ft_map_error("Error\nProbleme de malloc\n");
	is_path = find_path(data->p_x, data->p_y, map_copy);
	if (!is_path)
		ft_map_error("Error\nPas de chemin valide\n");
	i = 0;
	while (i < rows)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
