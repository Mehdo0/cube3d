/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:42:54 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 23:33:11 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	ft_parse_color(const char *str, int color[3])
{
	char	*tmp;
	char	*token;
	int		i;

	tmp = ft_strdup(str);
	if (!tmp)
		ft_map_error("Error\nMemory allocation failed\n");
	i = 0;
	token = ft_strtok(tmp, ",");
	while (token && i < 3)
	{
		color[i] = ft_atoi(token);
		i++;
		token = ft_strtok(NULL, ",");
	}
	free(tmp);
	if (i != 3)
		return (-1);
	return (0);
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
	printf("DEBUG: Adding map line: %s (height: %d)\n", line, config->map.height);
    tmp = realloc(config->map.grid, sizeof(char *) * (config->map.height + 1));
    if (!tmp) {
        printf("DEBUG: Failed to reallocate grid for line %d\n", config->map.height);
        ft_map_error("Error\nMemory allocation failed\n");
    }
    config->map.grid = tmp;
    printf("DEBUG: Duplicating line\n");
    config->map.grid[config->map.height] = ft_strdup(line);
    if (!config->map.grid[config->map.height]) {
        printf("DEBUG: Failed to duplicate line %d\n", config->map.height);
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
    
    printf("DEBUG: Opening file: %s\n", filename);
    fp = fopen(filename, "r");
    if (!fp) {
        printf("DEBUG: Failed to open file\n");
        ft_map_error("Error\nUnable to open file\n");
    }
    
    while (fgets(line, sizeof(line), fp))
    {
        line[ft_strcspn(line, "\n")] = '\0';
        printf("DEBUG: Read line: '%s'\n", line);
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
	initPlayer(&config->player, &config->map);
	return (config);
}