/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:07:22 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/31 11:52:26 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Fonction qui dessine le HUD avec transparence.
** Les pixels dont la couleur est 0x000000 (noir) sont considérés transparents.
*/
void draw_image_with_transparency(t_env *env, void *img, int pos_x, int pos_y, int img_w, int img_h)
{
    int bpp;
    int line_length;
    int endian;
    char *img_data;
    int x, y;
    int pixel;

    img_data = mlx_get_data_addr(img, &bpp, &line_length, &endian);
    for (y = 0; y < img_h; y++)
    {
        for (x = 0; x < img_w; x++)
        {
            pixel = *(int *)(img_data + y * line_length + x * (bpp / 8));
            
            // Vérifier si le pixel est noir (0x000000) -> Ne pas l'afficher
            if ((pixel & 0xFFFFFF) != 0x000000) // On ignore l'alpha
            {
                int dest_x = pos_x + x;
                int dest_y = pos_y + y;
                if (dest_x >= 0 && dest_x < SCREENWIDTH && dest_y >= 0 && dest_y < SCREENHEIGHT)
                {
                    char *dst = env->addr + (dest_y * env->line_length + dest_x * (env->bits_per_pixel / 8));
                    *(unsigned int *)dst = pixel;
                }
            }
        }
    }
}


void render_ceiling_floor(t_env *env)
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
    while (y < SCREENHEIGHT / 2)
    {
        x = 0;
        while (x < SCREENWIDTH)
        {
            char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
            *(unsigned int *)dst = ceiling_color;
            x++;
        }
        y++;
    }
    
    // Dessiner le sol (utiliser le buffer d'image)
    while (y < SCREENHEIGHT)
    {
        x = 0;
        while (x < SCREENWIDTH)
        {
            char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
            *(unsigned int *)dst = floor_color;
            x++;
        }
        y++;
    }
}

int fps_counter(t_env *env)
{
    static int prev_time = 0;
    static int frames = 0;
    static int fps = 0;
    int time;
    char fps_str[16];

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
    
    // 2) Créer la nouvelle image (frame) et récupérer son buffer
    env->img = mlx_new_image(env->mlx, SCREENWIDTH, SCREENHEIGHT);
    env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->line_length, &env->endian);
    
    // 3) Dessiner le plafond et le sol
    render_ceiling_floor(env);
    
    // 4) Lancer les rayons (mur, textures, etc.)
    castRays(env);
    
    // 5) Dessiner la minimap
    draw_minimap(env);
    
    // 6) Afficher l'image de la frame dans la fenêtre
    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    
    // 7) Afficher le HUD avec transparence (et non plus via mlx_put_image_to_window)
    if (env->img_textures->hud_img)
    {
        int hud_x = SCREENWIDTH - 170; 
        int hud_y = 10;
        draw_image_with_transparency(env,
            env->img_textures->hud_img,
            hud_x,
            hud_y,
            120,
            68);
    }
    if (env->img_textures->rifle_img)
    {
        int rifle_x = SCREENWIDTH - 822; 
        int rifle_y = SCREENHEIGHT - 504;
        draw_image_with_transparency(env,
            env->img_textures->rifle_img,
            rifle_x,
            rifle_y,
            822,
            504);
    }

    // 8) Afficher le compteur FPS (texte)
    fps_counter(env);
    
    // 9) Libérer l’image de la frame
    mlx_destroy_image(env->mlx, env->img);
    
    return (0);
}
