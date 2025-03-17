/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:20:36 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 23:24:47 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void draw_background(t_env *env, int start_x, int start_y, int size)
{
    int x;
    int y;
    
    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            char *dst = env->addr + ((start_y + y) * env->line_length + 
                        (start_x + x) * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = 0x44000000;  // Fond semi-transparent
            x++;
        }
        y++;
    }
}

void draw_walls(t_env *env, int start_x, int start_y, int tile_size)
{
    int x;
    int y;
    int draw_x;
    int draw_y;
    int color;
    
    y = 0;
    while (y < env->config->map.height)
    {
        x = 0;
        while (x < env->config->map.width)
        {
            if (y < env->config->map.height && x < (int)ft_strlen(env->config->map.grid[y]))
            {
                if (env->config->map.grid[y][x] == '1')
                    color = 0xFFFFFF;  // Murs en blanc
                else if (env->config->map.grid[y][x] == '0')
                    color = 0x444444;  // Espaces en gris
                else
                    color = 0x0000FF;  // Autre en bleu (portes, etc.)
                
                int ty = 0;
                while (ty < tile_size)
                {
                    int tx = 0;
                    while (tx < tile_size)
                    {
                        draw_x = start_x + x * tile_size + tx;
                        draw_y = start_y + y * tile_size + ty;
                        
                        if (draw_x >= 0 && draw_x < screenWidth && 
                            draw_y >= 0 && draw_y < screenHeight)
                        {
                            char *dst = env->addr + (draw_y * env->line_length + 
                                        draw_x * (env->bits_per_pixel / 8));
                            *(unsigned int*)dst = color;
                        }
                        tx++;
                    }
                    ty++;
                }
            }
            x++;
        }
        y++;
    }
}

void draw_player_direction(t_env *env, int player_x, int player_y, int size)
{
    t_player *player = &env->config->player;
    int dir_x, dir_y;
    int i;
    float angle;
    
    // Dessiner un cercle rouge pour la position du joueur
    for (int ty = -2; ty <= 2; ty++) {
        for (int tx = -2; tx <= 2; tx++) {
            if (tx*tx + ty*ty <= 4) {  // Cercle de rayon 2
                int draw_x = player_x + tx;
                int draw_y = player_y + ty;
                
                if (draw_x >= 0 && draw_x < screenWidth && 
                    draw_y >= 0 && draw_y < screenHeight) {
                    char *dst = env->addr + (draw_y * env->line_length + 
                                draw_x * (env->bits_per_pixel / 8));
                    *(unsigned int*)dst = 0xFF0000;  // Rouge
                }
            }
        }
    }
    
    // Dessiner une flèche pour indiquer la direction
    dir_x = player_x + player->dirX * size;
    dir_y = player_y + player->dirY * size;
    
    // Ligne centrale
    i = 0;
    while (i < size)
    {
        int draw_x = player_x + (int)(i * player->dirX / 2);
        int draw_y = player_y + (int)(i * player->dirY / 2);
        
        if (draw_x >= 0 && draw_x < screenWidth && 
            draw_y >= 0 && draw_y < screenHeight) {
            char *dst = env->addr + (draw_y * env->line_length + 
                        draw_x * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = 0xFFFF00;  // Jaune
        }
        i++;
    }
    
    // Pointe de la flèche (triangle)
    angle = atan2(player->dirY, player->dirX);
    for (int a = -2; a <= 2; a++)
    {
        float side_angle = angle + 3.14 / 4 * a / 2;
        int side_x = player_x + (int)(size/2 * player->dirX + 2 * cos(side_angle));
        int side_y = player_y + (int)(size/2 * player->dirY + 2 * sin(side_angle));
        
        if (side_x >= 0 && side_x < screenWidth && 
            side_y >= 0 && side_y < screenHeight) {
            char *dst = env->addr + (side_y * env->line_length + 
                        side_x * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = 0xFFFF00;  // Jaune
        }
    }
}

void draw_minimap(t_env *env)
{
    int minimap_size = 150;
    int tile_size = 5;
    int start_x = screenWidth - minimap_size - 10;
    int start_y = 10;
    t_player *player = &env->config->player;
    
    // Dessiner le fond de la minimap
    draw_background(env, start_x, start_y, minimap_size);
    
    // Dessiner les murs et espaces vides
    draw_walls(env, start_x, start_y, tile_size);
    
    // Dessiner la position et direction du joueur
    int player_x = start_x + (int)(player->posX * tile_size);
    int player_y = start_y + (int)(player->posY * tile_size);
    
    draw_player_direction(env, player_x, player_y, tile_size * 2);
    
    // Ajouter un cadre à la minimap
    int border_color = 0xFFFFFF;
    
    // Ligne horizontale supérieure
    for (int x = start_x - 1; x <= start_x + minimap_size; x++) {
        char *dst = env->addr + ((start_y - 1) * env->line_length + 
                    x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
    
    // Ligne horizontale inférieure
    for (int x = start_x - 1; x <= start_x + minimap_size; x++) {
        char *dst = env->addr + ((start_y + minimap_size) * env->line_length + 
                    x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
    
    // Ligne verticale gauche
    for (int y = start_y - 1; y <= start_y + minimap_size; y++) {
        char *dst = env->addr + (y * env->line_length + 
                    (start_x - 1) * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
    
    // Ligne verticale droite
    for (int y = start_y - 1; y <= start_y + minimap_size; y++) {
        char *dst = env->addr + (y * env->line_length + 
                    (start_x + minimap_size) * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
}