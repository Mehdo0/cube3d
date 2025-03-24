/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:53:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/24 21:14:21 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <fcntl.h>


void	ft_check_borders(t_config *config)
{
	int	x, y;
	int	player_count = 0; // Compte le nombre de 'N', 'E', 'W' ou 'S'

	if (config->map.height == 0)
		ft_map_error("Error\nLa map ne peut pas être vide\n");
	y = 0;
	while (y < config->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(config->map.grid[y]))
		{
			char c = config->map.grid[y][x];

			// Vérification des caractères valides
			if (c != '0' && c != '1' && c != 'N' && c != 'E' &&
				c != 'S' && c != 'W' && c != ' ')
				ft_map_error("Error\nLa map ne doit contenir que '0', '1', 'N', 'W', 'E', 'S' ou ' '\n");

			// Vérification des bordures (doivent être des murs ou des espaces)
			else if ((y == 0 || x == 0 || y == config->map.height - 1 || 
                    x == (int)ft_strlen(config->map.grid[y]) - 1) && 
                    c != '1' && c != ' ')
				ft_map_error("Error\nLa map doit être entourée de murs ('1') ou d'espaces (' ')\n");

			// Vérification des espaces adjacents à des zones jouables
			else if (c == ' ')
			{
				if ((x > 0 && config->map.grid[y][x-1] == '0') ||
					(y > 0 && config->map.grid[y-1][x] == '0') ||
					(x < (int)ft_strlen(config->map.grid[y]) - 1 && config->map.grid[y][x+1] == '0') ||
					(y < config->map.height - 1 && x < (int)ft_strlen(config->map.grid[y+1]) && config->map.grid[y+1][x] == '0'))
					ft_map_error("Error\nLes espaces ne peuvent pas être adjacents à des zones jouables\n");
			}

			// Compter le joueur (N, E, W, S)
			if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
				player_count++;

			x++;
		}
		y++;
	}

	// Vérifier qu'il y a exactement un joueur sur la carte
	if (player_count != 1)
		ft_map_error("Error\nLa map doit contenir exactement un seul joueur ('N', 'E', 'W' ou 'S')\n");
}
