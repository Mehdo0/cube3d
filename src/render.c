/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:07:22 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/25 16:48:10 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void    render_ceiling_floor(t_env *env)
{
    int x;
    int y;
    int ceiling_color;
    int floor_color;
    
    ceiling_color = create_rgb(env->config->ceiling[0], 
                             env->config->ceiling[1], 
                             env->config->ceiling[2]);
    floor_color = create_rgb(env->config->floor[0], 
                           env->config->floor[1], 
                           env->config->floor[2]);
    
    // Dessiner le plafond (utiliser le buffer d'image)
    y = 0;
    while (y < screenHeight / 2)
    {
        x = 0;
        while (x < screenWidth)
        {
            char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
            *(unsigned int *)dst = ceiling_color;
            x++;
        }
        y++;
    }
    
    // Dessiner le sol (utiliser le buffer d'image)
    while (y < screenHeight)
    {
        x = 0;
        while (x < screenWidth)
        {
            char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
            *(unsigned int *)dst = floor_color;
            x++;
        }
        y++;
    }
}

int    fps_counter(t_env *env)
{
    static int    prev_time = 0;
    static int    frames = 0;
    static int    fps = 0;
    int            time;
    char        fps_str[16];

    frames++;
    time = clock() / (CLOCKS_PER_SEC / 1000);  // Temps en millisecondes
    
    // Mettre à jour le FPS chaque seconde
    if (time - prev_time >= 1000)
    {
        fps = frames;
        frames = 0;
        prev_time = time;
    }
    
    // Afficher le FPS dans le coin supérieur gauche
    sprintf(fps_str, "FPS: %d", fps);
    mlx_string_put(env->mlx, env->win, 10, 20, 0xFFFFFF, fps_str);
    
    return (fps);
}


int render_frame(t_env *env)
{
    // 1) Déplacer le joueur
    float moveSpeed = 0.04;
    float rotSpeed = 0.04;
    movePlayer(env, moveSpeed, rotSpeed);
    
    // 2) Créer une nouvelle image (frame) et récupérer son buffer
    env->img = mlx_new_image(env->mlx, screenWidth, screenHeight);
    env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->line_length, &env->endian);
    
    // 3) Dessiner le plafond et le sol
    render_ceiling_floor(env);
    
    // 4) Lancer les rayons (walls, textures, etc.)
    castRays(env);
    
    // 5) Dessiner la minimap
    draw_minimap(env);
    
    // 6) Afficher l'image de la frame dans la fenêtre
    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    
    // 7) Afficher le HUD (toujours au-dessus)
    if (env->img_textures->hud_img)
    {
        int hud_x = screenWidth - 150; 
        int hud_y = 10;
        mlx_put_image_to_window(env->mlx, env->win, env->img_textures->hud_img, hud_x, hud_y);
    }

    // 8) Afficher le compteur FPS (texte)
    fps_counter(env);
    
    // 9) Libérer l’image de la frame
    mlx_destroy_image(env->mlx, env->img);

    
    return (0);
}
