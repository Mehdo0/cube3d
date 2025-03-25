/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:20:36 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/25 16:22:39 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

// On modifie draw_background pour qu'elle prenne en paramètres
// la largeur et la hauteur en pixels de la zone à remplir.
void draw_background(t_env *env, int start_x, int start_y, int width, int height)
{
    int x;
    int y;
    
    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
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
                    color = 0x0000FF;  // Autre (ex. portes) en bleu
                
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
    
    // Dessiner un petit cercle rouge pour la position du joueur
    for (int ty = -2; ty <= 2; ty++) {
        for (int tx = -2; tx <= 2; tx++) {
            if (tx*tx + ty*ty <= 150) {  // Cercle de rayon 2
                int draw_x = player_x + tx;
                int draw_y = player_y + ty;
                
                if (draw_x >= 0 && draw_x < screenWidth && 
                    draw_y >= 0 && draw_y < screenHeight) {
                    char *dst = env->addr + (draw_y * env->line_length + 
                                draw_x * (env->bits_per_pixel / 8));
                    *(unsigned int*)dst = 0xFFFFFF;  // Blanc
                }
            }
        }
    }
    
    // Dessiner une flèche indiquant la direction
    dir_x = player_x + player->dirX * size;
    dir_y = player_y + player->dirY * size;
    
    // Ligne centrale de la flèche
    i = 0;
    while (i < size)
    {
        int draw_x = player_x + (int)(i * player->dirX / 2);
        int draw_y = player_y + (int)(i * player->dirY / 2);
        
        if (draw_x >= 0 && draw_x < screenWidth && 
            draw_y >= 0 && draw_y < screenHeight) {
            char *dst = env->addr + (draw_y * env->line_length + 
                        draw_x * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = 0xFF0000;  // Rouge
        }
        i++;
    }
}

void draw_minimap(t_env *env)
{
    // Fixer la taille d'une tuile en pixels
    int tile_size = 10;
    // La largeur et la hauteur de la minimap dépendent de la taille de la carte
    int map_width = env->config->map.width;
    int map_height = env->config->map.height;
    int minimap_width = map_width * tile_size;
    int minimap_height = map_height * tile_size;
    
    // Position de la minimap dans l'écran (par exemple, en haut à droite)
    int start_x = 50;
    int start_y = screenHeight - minimap_height - 50;
    
    t_player *player = &env->config->player;
    
    // Dessiner le fond de la minimap (la zone a exactement la taille de la map en pixels)
    draw_background(env, start_x, start_y, minimap_width, minimap_height);
    
    // Dessiner les murs et espaces vides en fonction de la map
    draw_walls(env, start_x, start_y, tile_size);
    
    // Dessiner la position et la direction du joueur
    int player_x = start_x + (int)(player->posX * tile_size);
    int player_y = start_y + (int)(player->posY * tile_size);
    
    draw_player_direction(env, player_x, player_y, tile_size * 2);
    
    // Ajouter un cadre à la minimap
    int border_color = 0xFFFFFF;
    
    // Ligne horizontale supérieure
    for (int x = start_x - 1; x <= start_x + minimap_width; x++) {
        char *dst = env->addr + ((start_y - 1) * env->line_length +
                    x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
    
    // Ligne horizontale inférieure
    for (int x = start_x - 1; x <= start_x + minimap_width; x++) {
        char *dst = env->addr + ((start_y + minimap_height) * env->line_length +
                    x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
    
    // Ligne verticale gauche
    for (int y = start_y - 1; y <= start_y + minimap_height; y++) {
        char *dst = env->addr + (y * env->line_length +
                    (start_x - 1) * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
    
    // Ligne verticale droite
    for (int y = start_y - 1; y <= start_y + minimap_height; y++) {
        char *dst = env->addr + (y * env->line_length +
                    (start_x + minimap_width) * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = border_color;
    }
}
