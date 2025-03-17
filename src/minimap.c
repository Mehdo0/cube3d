/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:20:36 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 22:48:55 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void draw_minimap(t_env *env)
{
    int minimap_size = 150;
    int tile_size = 5;
    int start_x = screenWidth - minimap_size - 10;
    int start_y = 10;
    
    // Dessiner le fond de la minimap
    for (int y = 0; y < minimap_size; y++) {
        for (int x = 0; x < minimap_size; x++) {
            char *dst = env->addr + ((start_y + y) * env->line_length + (start_x + x) * (env->bits_per_pixel / 8));
            *(unsigned int*)dst = 0x44000000;  // Fond semi-transparent
        }
    }
    
    // Dessiner les murs et espaces vides
    for (int y = 0; y < env->config->map.height; y++) {
        for (int x = 0; x < env->config->map.width; x++) {
            if (y < env->config->map.height && x < (int)ft_strlen(env->config->map.grid[y])) {
                int color = env->config->map.grid[y][x] == '1' ? 0xFFFFFF : 0x444444;
                
                for (int ty = 0; ty < tile_size; ty++) {
                    for (int tx = 0; tx < tile_size; tx++) {
                        int draw_x = start_x + x * tile_size + tx;
                        int draw_y = start_y + y * tile_size + ty;
                        
                        if (draw_x >= 0 && draw_x < screenWidth && draw_y >= 0 && draw_y < screenHeight) {
                            char *dst = env->addr + (draw_y * env->line_length + draw_x * (env->bits_per_pixel / 8));
                            *(unsigned int*)dst = color;
                        }
                    }
                }
            }
        }
    }
    
    // Dessiner la position du joueur
    int player_x = start_x + (int)(env->config->player.posX * tile_size);
    int player_y = start_y + (int)(env->config->player.posY * tile_size);
    
    for (int ty = -2; ty <= 2; ty++) {
        for (int tx = -2; tx <= 2; tx++) {
            if (tx*tx + ty*ty <= 4) {  // Cercle de rayon 2
                int draw_x = player_x + tx;
                int draw_y = player_y + ty;
                
                if (draw_x >= 0 && draw_x < screenWidth && draw_y >= 0 && draw_y < screenHeight) {
                    char *dst = env->addr + (draw_y * env->line_length + draw_x * (env->bits_per_pixel / 8));
                    *(unsigned int*)dst = 0xFF0000;  // Rouge
                }
            }
        }
    }
}
