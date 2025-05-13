/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:42:54 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/13 17:09:30 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	ft_parse_direction(t_config *config, char *trimmed, char dir)
{
	char	*path;

	path = trimmed + 2;
	while (*path && ft_isspace((unsigned char)*path))
		path++;
	if (dir == 'N')
		config->no = ft_strdup(path);
	else if (dir == 'S')
		config->so = ft_strdup(path);
	else if (dir == 'W')
		config->we = ft_strdup(path);
	else if (dir == 'E')
		config->ea = ft_strdup(path);
}

static void	ft_parse_config_line(t_config *config, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " ");
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		ft_parse_direction(config, trimmed, 'N');
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		ft_parse_direction(config, trimmed, 'S');
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		ft_parse_direction(config, trimmed, 'W');
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		ft_parse_direction(config, trimmed, 'E');
	else if (trimmed[0] == 'F')
		ft_parse_color_line(config, trimmed, 'F');
	else if (trimmed[0] == 'C')
		ft_parse_color_line(config, trimmed, 'C');
	free(trimmed);
}

static void	ft_parse_file(const char *filename, t_config *config)
{
	FILE	*fp;
	char	line[MAX_LINE];
	int		map_started;

	map_started = 0;
	fp = fopen(filename, "r");
	if (!fp)
		ft_map_error("Error\nUnable to open file\n");
	while (fgets(line, sizeof(line), fp))
	{
		line[ft_strcspn(line, "\n")] = '\0';
		if (line[0] == '\0')
			continue ;
		if (!map_started && (ft_isdigit(line[0]) || line[0] == ' '))
			map_started = 1;
		if (map_started)
			ft_add_map_line(config, line);
		else
			ft_parse_config_line(config, line);
	}
	fclose(fp);
}

t_config	*ft_init_and_parse_map(const char *filename)
{
	t_config	*config;

	config = ft_init_config();
	ft_parse_file(filename, config);
	init_player(&config->player, &config->map);
	if ((config->floor[0] < 0 || config->floor[1] < 0 || config->floor[2] < 0)
		|| (config->ceiling[0] < 0 || config->ceiling[1] < 0
			|| config->ceiling[2] < 0)
		|| !config->no || !config->so || !config->we || !config->ea
		|| config->map.height == 0)
		ft_map_error("Error\nInvalid color format\n");
	return (config);
}
