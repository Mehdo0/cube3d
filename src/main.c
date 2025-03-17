/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:19:01 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 14:19:03 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_map_error("Error\nInvalid number of arguments\n");
	t_config *config = ft_init_and_parse_map(av[1]);	
	for (int i, j = 0; i < config->map_height; i++)
	{
		j = 0;
		while (j < config->map_width)
		{
			printf("%c", config->map[i][j]);
			j++;
		}
		printf("\n");
	}
	void *mlx = mlx_init();
	mlx_new_window(mlx, 1900, 1000, "oui");
	mlx_loop(mlx);

	t_env	env;
	
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, 1920, 1080, "Les blagues room");
	handle_hook(&env);
	mlx_loop(env.mlx);
	return (0);
}
