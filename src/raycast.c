/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:02:32 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 23:23:45 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void castRays(t_env *env)
{
    t_player *player = &env->config->player;
    t_map *map = &env->config->map;
    
    // Pour chaque colonne de l'écran
    for (int x = 0; x < screenWidth; x++) {
        // Calculer la position x sur le plan de la caméra
        float cameraX = 2 * x / (float)screenWidth - 1; // -1 pour gauche, 0 pour centre, 1 pour droite
        float rayDirX = player->dirX + player->planeX * cameraX;
        float rayDirY = player->dirY + player->planeY * cameraX;
        
        // Position initiale = position du joueur
        int mapX = (int)player->posX;
        int mapY = (int)player->posY;
        
        // Longueur du rayon de la position actuelle à la prochaine ligne x ou y
        float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        
        // Direction des pas et distance initiale aux bords
        int stepX, stepY;
        float sideDistX, sideDistY;
        
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
        }
        
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
        }
        
        // Algorithme DDA - Avance jusqu'à toucher un mur
        int hit = 0;  // Mur touché?
        int side;     // N/S ou E/W?
        
        while (hit == 0) {
            // Sauter au prochain carré de la carte
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;  // Touche un mur vertical (face E/W)
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;  // Touche un mur horizontal (face N/S)
            }
            
            // Vérifier si le rayon a touché un mur
            if (mapX < 0 || mapY < 0 || mapX >= map->width || mapY >= map->height || 
                map->grid[mapY][mapX] == '1') {
                hit = 1;
            }
        }
        
        // Calculer la distance perpendiculaire (évite l'effet fish-eye)
        float perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / rayDirY;
        
        // Calculer la hauteur de la ligne à dessiner
        int lineHeight = (int)(screenHeight / perpWallDist);
        
        // Calculer le pixel de début et de fin
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
        
        // Déterminer quelle texture utiliser selon le mur touché
        void *texture;
        if (side == 0) {
            if (stepX > 0)
                texture = env->img_textures->wall_E;  // Mur est
            else
                texture = env->img_textures->wall_W;  // Mur ouest
        } else {
            if (stepY > 0)
                texture = env->img_textures->wall_S;  // Mur sud
            else
                texture = env->img_textures->wall_N;  // Mur nord
        }
        
        // Calculer la position exacte où le mur a été touché
        float wallX;
        if (side == 0)
            wallX = player->posY + perpWallDist * rayDirY;
        else
            wallX = player->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * texWidth);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
            texX = texWidth - texX - 1;
        
        // Dessiner la colonne texturée
        drawTexturedLine(env, x, drawStart, drawEnd, texture, texX);
    }
}


void drawVerticalLine(t_env *env, int x, int drawStart, int drawEnd, int color) {
    int y;
    
    y = drawStart;
    while (y <= drawEnd)
    {
        // Utilisez mlx_pixel_put pour un rendu simple (mais lent)
        // mlx_pixel_put(env->mlx, env->win, x, y, color);
        
        // Ou mieux, utilisez un buffer d'image pour un rendu plus rapide
        char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        
        y++;
    }
}

void movePlayer(t_env *env, float moveSpeed, float rotSpeed)
{
    t_player *player = &env->config->player;
    t_map *map = &env->config->map;
    float collision_margin = 0.2;  // Marge pour éviter de coller aux murs
    
    // Avancer
    if (env->keys.up) {
        float newX = player->posX + player->dirX * moveSpeed;
        float newY = player->posY + player->dirY * moveSpeed;
        
        // Vérifier si la nouvelle position est valide (pas dans un mur)
        if (newX >= 0 && newY >= 0 && 
            newX < map->width && newY < map->height) {
            // Vérifier les collisions avec marge
            if (map->grid[(int)player->posY][(int)(newX + collision_margin * player->dirX)] == '0' &&
                map->grid[(int)player->posY][(int)(newX - collision_margin * player->dirX)] == '0')
                player->posX = newX;
            if (map->grid[(int)(newY + collision_margin * player->dirY)][(int)player->posX] == '0' &&
                map->grid[(int)(newY - collision_margin * player->dirY)][(int)player->posX] == '0')
                player->posY = newY;
        }
    }
    
    // Reculer
    if (env->keys.down) {
        float newX = player->posX - player->dirX * moveSpeed;
        float newY = player->posY - player->dirY * moveSpeed;
        
        if (newX >= 0 && newY >= 0 && 
            newX < map->width && newY < map->height) {
            // Vérifier les collisions avec marge
            if (map->grid[(int)player->posY][(int)(newX + collision_margin * -player->dirX)] == '0' &&
                map->grid[(int)player->posY][(int)(newX - collision_margin * -player->dirX)] == '0')
                player->posX = newX;
            if (map->grid[(int)(newY + collision_margin * -player->dirY)][(int)player->posX] == '0' &&
                map->grid[(int)(newY - collision_margin * -player->dirY)][(int)player->posX] == '0')
                player->posY = newY;
        }
    }
    
    // Déplacement latéral gauche
    if (env->keys.strafe_left) {
        float dirX_perp = -player->dirY;  // Direction perpendiculaire (à gauche)
        float dirY_perp = player->dirX;
        
        float newX = player->posX + dirX_perp * moveSpeed;
        float newY = player->posY + dirY_perp * moveSpeed;
        
        if (newX >= 0 && newY >= 0 && 
            newX < map->width && newY < map->height) {
            if (map->grid[(int)player->posY][(int)newX] == '0')
                player->posX = newX;
            if (map->grid[(int)newY][(int)player->posX] == '0')
                player->posY = newY;
        }
    }
    
    // Déplacement latéral droit
    if (env->keys.strafe_right) {
        float dirX_perp = player->dirY;  // Direction perpendiculaire (à droite)
        float dirY_perp = -player->dirX;
        
        float newX = player->posX + dirX_perp * moveSpeed;
        float newY = player->posY + dirY_perp * moveSpeed;
        
        if (newX >= 0 && newY >= 0 && 
            newX < map->width && newY < map->height) {
            if (map->grid[(int)player->posY][(int)newX] == '0')
                player->posX = newX;
            if (map->grid[(int)newY][(int)player->posX] == '0')
                player->posY = newY;
        }
    }
    
    // Tourner à gauche
    if (env->keys.left) {
        // Rotation de la matrice
        float oldDirX = player->dirX;
        player->dirX = player->dirX * cos(rotSpeed) - player->dirY * sin(rotSpeed);
        player->dirY = oldDirX * sin(rotSpeed) + player->dirY * cos(rotSpeed);
        
        float oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
        player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
    }
    
    // Tourner à droite
    if (env->keys.right) {
        // Rotation de la matrice (sens inverse)
        float oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-rotSpeed) - player->dirY * sin(-rotSpeed);
        player->dirY = oldDirX * sin(-rotSpeed) + player->dirY * cos(-rotSpeed);
        
        float oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
        player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
    }
}

void drawTexturedLine(t_env *env, int x, int drawStart, int drawEnd, void *texture, int texX) {
    int lineHeight = drawEnd - drawStart;
    
    char *texData;
    int texBpp, texLineLength, texEndian;
    
    // Obtenir les données de la texture
    texData = mlx_get_data_addr(texture, &texBpp, &texLineLength, &texEndian);
    
    // Dessiner la ligne verticale
    for (int y = drawStart; y < drawEnd; y++) {
        int texY = (y - drawStart) * texHeight / lineHeight;
        
        // Calculer la couleur
        char *texPixel = texData + (texY * texLineLength + texX * (texBpp / 8));
        int color = *(unsigned int*)texPixel;
        
        // Dessiner le pixel
        char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
