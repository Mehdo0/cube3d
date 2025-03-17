/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:19:01 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 22:48:04 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int main(int ac, char **av)
{
    t_env env;
    
    if (ac != 2)
        ft_map_error("Error\nInvalid number of arguments\n");
    
    // Initialiser MLX et la fenêtre
    env.mlx = mlx_init();
    env.win = mlx_new_window(env.mlx, screenWidth, screenHeight, "Cube3D");
    
    // Initialiser la configuration et parser la carte
    env.config = ft_init_and_parse_map(av[1]);

	// Dans main.c, après avoir initialisé env.config
	env.config = ft_init_and_parse_map(av[1]);
	load_textures(&env);
    
    // Configurer les hooks pour les événements
    mlx_hook(env.win, 2, 1L<<0, key_press, &env);   // Touche pressée
    mlx_hook(env.win, 3, 1L<<1, key_release, &env); // Touche relâchée
    mlx_hook(env.win, 17, 0, close_window, &env);   // Fermeture de fenêtre
    
    // Configurer la fonction de rendu
    mlx_loop_hook(env.mlx, render_frame, &env);
    
    // Lancer la boucle principale
    mlx_loop(env.mlx);
    
    return (0);
}
