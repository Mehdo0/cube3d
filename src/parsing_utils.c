/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:41:17 by kgiraud           #+#    #+#             */
/*   Updated: 2025/06/05 11:43:34 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	parse_color_boucle(char *tmp, char *token, int i, int color[3])
{
	int	value;

	while (token)
	{
		if (i >= 3)
		{
			free(tmp);
			return (-1);
		}
		value = ft_atoi(token);
		if (value < 0 || value > 255)
		{
			free(tmp);
			return (-1);
		}
		color[i++] = value;
		token = ft_strtok(NULL, ",");
	}
	free(tmp);
	if (i != 3)
		return (-1);
	return (0);
}

int	ft_parse_color(const char *str, int color[3])
{
	char	*tmp;
	char	*token;
	int		i;

	if (!str || !*str)
		return (-1);
	tmp = ft_strdup(str);
	if (!tmp)
		ft_map_error("Error\nMemory allocation failed\n");
	i = 0;
	token = ft_strtok(tmp, ",");
	if (!token)
	{
		free(tmp);
		return (-1);
	}
	return (parse_color_boucle(tmp, token, i, color));
}

void	ft_parse_color_line(t_config *config, char *trimmed, char type)
{
	char	*color_str;

	color_str = trimmed + 1;
	while (*color_str && ft_isspace((unsigned char)*color_str))
		color_str++;
	if (type == 'F')
	{
		if (ft_parse_color(color_str, config->floor) != 0)
			ft_map_error("Error\nInvalid floor color format\n");
	}
	else if (type == 'C')
	{
		if (ft_parse_color(color_str, config->ceiling) != 0)
			ft_map_error("Error\nInvalid ceiling color format\n");
	}
	else
		ft_map_error("Error\nMissing colors\n");
}

void	ft_add_map_line(t_config *config, char *line)
{
	char	**tmp;

	tmp = realloc(config->map.grid, sizeof(char *) * (config->map.height + 1));
	if (!tmp)
		ft_map_error("Error\nMemory allocation failed\n");
	config->map.grid = tmp;
	config->map.grid[config->map.height] = ft_strdup(line);
	if (!config->map.grid[config->map.height])
		ft_map_error("Error\nMemory allocation failed\n");
	if ((int)ft_strlen(line) > config->map.width)
		config->map.width = ft_strlen(line);
	config->map.height++;
}

void	ft_free_config(t_config *config)
{
	int	i;

	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	i = 0;
	while (i < config->map.height)
	{
		free(config->map.grid[i]);
		i++;
	}
	free(config->map.grid);
}
