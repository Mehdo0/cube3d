/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:42:54 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/26 21:26:59 by mmouaffa         ###   ########.fr       */
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
		if (!ft_isdigit(token))
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

static int	ft_parse_color(const char *str, int color[3])
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


static void	ft_parse_config_line(t_config *config, char *line)
{
	char	*trimmed;
	char	*path;
	char	*color_str;

	trimmed = ft_strtrim(line, " ");
	if (ft_strncmp(trimmed, "NO", 2) == 0)
	{
		path = trimmed + 2;
		while (*path && ft_isspace((unsigned char)*path))
			path++;
		config->no = ft_strdup(path);
	}
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
	{
		path = trimmed + 2;
		while (*path && ft_isspace((unsigned char)*path))
			path++;
		config->so = ft_strdup(path);
	}
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
	{
		path = trimmed + 2;
		while (*path && ft_isspace((unsigned char)*path))
			path++;
		config->we = ft_strdup(path);
	}
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
	{
		path = trimmed + 2;
		while (*path && ft_isspace((unsigned char)*path))
			path++;
		config->ea = ft_strdup(path);
	}
	else if (trimmed[0] == 'F')
	{
		color_str = trimmed + 1;
		while (*color_str && ft_isspace((unsigned char)*color_str))
			color_str++;
		if (ft_parse_color(color_str, config->floor) != 0)
			ft_map_error("Error\nInvalid floor color format\n");
	}
	else if (trimmed[0] == 'C')
	{
		color_str = trimmed + 1;
		while (*color_str && ft_isspace((unsigned char)*color_str))
			color_str++;
		if (ft_parse_color(color_str, config->ceiling) != 0)
			ft_map_error("Error\nInvalid ceiling color format\n");
	}
}

static void	ft_add_map_line(t_config *config, char *line)
{
	char **tmp;
    tmp = realloc(config->map.grid, sizeof(char *) * (config->map.height + 1));
    if (!tmp) {
        ft_map_error("Error\nMemory allocation failed\n");
    }
    config->map.grid = tmp;
    config->map.grid[config->map.height] = ft_strdup(line);
    if (!config->map.grid[config->map.height]) {
        ft_map_error("Error\nMemory allocation failed\n");
    }
	if ((int)ft_strlen(line) > config->map.width)
		config->map.width = ft_strlen(line);
	config->map.height++;
}

static void	ft_parse_file(const char *filename, t_config *config)
{
	FILE *fp;
    char line[MAX_LINE];
    int map_started = 0;
    
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

t_config	*ft_init_and_parse_map(const char *filename)
{
	t_config	*config;

	config = ft_init_config();
	ft_parse_file(filename, config);
	ft_check_borders(config);
	initPlayer(&config->player, &config->map);
	if (config->floor[0] < 0 || config->floor[1] < 0 || config->floor[2] < 0 ||
		config->ceiling[0] < 0 || config->ceiling[1] < 0 || config->ceiling[2] < 0
		|| !config->no || !config->so || !config->we || !config->ea
		|| config->map.height == 0)
		ft_map_error("Error\nInvalid color format\n");
	return (config);
}
