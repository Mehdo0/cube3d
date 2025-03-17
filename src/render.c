/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:07:22 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 22:44:08 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int render_frame(t_env *env)
{
    // Déplacer le joueur
    float moveSpeed = 0.05;
    float rotSpeed = 0.03;
    movePlayer(env, moveSpeed, rotSpeed);
    
    // Créer une nouvelle image à chaque frame
    env->img = mlx_new_image(env->mlx, screenWidth, screenHeight);
    env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->line_length, &env->endian);
    
    // Dessiner le plafond (utiliser le buffer d'image)
    for (int y = 0; y < screenHeight / 2; y++) {
        for (int x = 0; x < screenWidth; x++) {
            int color = create_rgb(env->config->ceiling[0], env->config->ceiling[1], env->config->ceiling[2]);
            char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = color;
        }
    }
    
    // Dessiner le sol (utiliser le buffer d'image)
    for (int y = screenHeight / 2; y < screenHeight; y++) {
        for (int x = 0; x < screenWidth; x++) {
            int color = create_rgb(env->config->floor[0], env->config->floor[1], env->config->floor[2]);
            char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = color;
        }
    }
    
    // Lancer les rayons
    castRays(env);
    
    // Afficher l'image
    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    
    // Libérer l'image
    mlx_destroy_image(env->mlx, env->img);
    
    return (0);
}
