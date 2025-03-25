/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:02:32 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/25 15:37:40 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void castRays(t_env *env)
{
    t_player *player = &env->config->player;
    t_map    *map    = &env->config->map;

    for (int x = 0; x < screenWidth; x++)
    {
        // Position "cameraX" sur le plan : de -1 (gauche) à +1 (droite)
        float cameraX = 2.0f * x / (float)screenWidth - 1.0f;

        // Direction du rayon
        float rayDirX = player->dirX   + player->planeX * cameraX;
        float rayDirY = player->dirY   + player->planeY * cameraX;

        // Case map courante (en int)
        int mapX = (int)(player->posX);
        int mapY = (int)(player->posY);

        // Distances pour avancer «case par case» (DDA)
        float deltaDistX = (fabs(rayDirX) < 1e-8) ? 1e30 : fabs(1.0f / rayDirX);
        float deltaDistY = (fabs(rayDirY) < 1e-8) ? 1e30 : fabs(1.0f / rayDirY);

        // Calcul sideDistX / sideDistY + stepX / stepY
        int stepX, stepY;
        float sideDistX, sideDistY;
        if (rayDirX < 0)
        {
            stepX     = -1;
            sideDistX = (player->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX     = 1;
            sideDistX = (mapX + 1.0f - player->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY     = -1;
            sideDistY = (player->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY     = 1;
            sideDistY = (mapY + 1.0f - player->posY) * deltaDistY;
        }

        // Parcours DDA jusqu’au mur
        int hit  = 0;   // mur touché ?
        int side = 0;   // orientation (0 = X, 1 = Y)
        while (!hit)
        {
            // On avance «en X» ou «en Y» selon la plus petite sideDist
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // mur vertical
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // mur horizontal
            }
            // Vérifie s’il y a un mur ou si on sort de la map
            if (mapX < 0 || mapY < 0 || mapX >= map->width || mapY >= map->height
                || map->grid[mapY][mapX] == '1')
            {
                hit = 1;
            }
        }

        // Distance perpendiculaire pour éviter le fish-eye
        float perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - player->posX + (1 - stepX) / 2.0f) / rayDirX;
        else
            perpWallDist = (mapY - player->posY + (1 - stepY) / 2.0f) / rayDirY;

        // Calcul de la hauteur de colonne
        int lineHeight = (int)(screenHeight / perpWallDist + 10);

        // Position en haut et en bas sur l’écran (sans la clamping encore)
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        int drawEnd   =  lineHeight / 2 + screenHeight / 2;

        // Choix de la texture selon la face touchée
        void *texture = NULL;
        if (side == 0)
        {
            // Rayon E ou W
            if (stepX > 0)
                texture = env->img_textures->wall_E; 
            else
                texture = env->img_textures->wall_W;
        }
        else
        {
            // Rayon S ou N
            if (stepY > 0)
                texture = env->img_textures->wall_S;
            else
                texture = env->img_textures->wall_N;
        }

        // Calcul de la coordonnée X sur la texture [0..texWidth-1]
        float wallX;
        if (side == 0)
            wallX = player->posY + perpWallDist * rayDirY;
        else
            wallX = player->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (float)texWidth);
        // Inversion éventuelle de la texture (pour éviter de la dessiner à l’envers)
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
            texX = texWidth - texX - 1;

        // Clamping vertical (on ne redimensionne PAS, on coupe juste ce qui sort de l’écran)
        if (drawStart < 0)
            drawStart = 0;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        // Dessin de la bande texturée
        drawTexturedLine(env, x, drawStart, drawEnd, texture, texX, lineHeight);
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

static int isFree(float x, float y, t_map *map)
{
    return map->grid[(int)y][(int)x] == '0';
}

void movePlayer(t_env *env, float moveSpeed, float rotSpeed)
{
    t_player *player = &env->config->player;
    t_map *map = &env->config->map;
    float collision_margin = 0.15;  // Ajustable pour éviter les collisions

    // Avancer
    if (env->keys.up) {
        float newX = player->posX + player->dirX * moveSpeed;
        float newY = player->posY + player->dirY * moveSpeed;

        // Vérification X, Y et diagonale pour éviter les collisions aux coins
        if (isFree(newX + collision_margin, player->posY, map) &&
            isFree(newX - collision_margin, player->posY, map) &&
            isFree(newX, newY, map))
            player->posX = newX;
        if (isFree(player->posX, newY + collision_margin, map) &&
            isFree(player->posX, newY - collision_margin, map) &&
            isFree(newX, newY, map))
            player->posY = newY;
    }

    // Reculer
    if (env->keys.down) {
        float newX = player->posX - player->dirX * moveSpeed;
        float newY = player->posY - player->dirY * moveSpeed;

        if (isFree(newX + collision_margin, player->posY, map) &&
            isFree(newX - collision_margin, player->posY, map) &&
            isFree(newX, newY, map))
            player->posX = newX;
        if (isFree(player->posX, newY + collision_margin, map) &&
            isFree(player->posX, newY - collision_margin, map) &&
            isFree(newX, newY, map))
            player->posY = newY;
    }

    // Déplacement latéral gauche
    if (env->keys.strafe_left) {
        float dirX_perp = -player->dirY;
        float dirY_perp = player->dirX;
        float newX = player->posX + dirX_perp * moveSpeed;
        float newY = player->posY + dirY_perp * moveSpeed;

        if (isFree(newX + collision_margin, player->posY, map) &&
            isFree(newX - collision_margin, player->posY, map) &&
            isFree(newX, newY, map))
            player->posX = newX;
        if (isFree(player->posX, newY + collision_margin, map) &&
            isFree(player->posX, newY - collision_margin, map) &&
            isFree(newX, newY, map))
            player->posY = newY;
    }

    // Déplacement latéral droit
    if (env->keys.strafe_right) {
        float dirX_perp = player->dirY;
        float dirY_perp = -player->dirX;
        float newX = player->posX + dirX_perp * moveSpeed;
        float newY = player->posY + dirY_perp * moveSpeed;

        if (isFree(newX + collision_margin, player->posY, map) &&
            isFree(newX - collision_margin, player->posY, map) &&
            isFree(newX, newY, map))
            player->posX = newX;
        if (isFree(player->posX, newY + collision_margin, map) &&
            isFree(player->posX, newY - collision_margin, map) &&
            isFree(newX, newY, map))
            player->posY = newY;
    }

    // Tourner à gauche
    if (env->keys.left) {
        float oldDirX = player->dirX;
        player->dirX = player->dirX * cos(rotSpeed) - player->dirY * sin(rotSpeed);
        player->dirY = oldDirX * sin(rotSpeed) + player->dirY * cos(rotSpeed);

        float oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
        player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
    }

    // Tourner à droite
    if (env->keys.right) {
        float oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-rotSpeed) - player->dirY * sin(-rotSpeed);
        player->dirY = oldDirX * sin(-rotSpeed) + player->dirY * cos(-rotSpeed);

        float oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
        player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
    }
}



void drawTexturedLine(t_env *env,
                      int x, int drawStart, int drawEnd,
                      void *texture, int texX, int lineHeight)
{
    if (!texture)
        return;

    int bpp, size_line, endian;
    char *texData = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
    if (!texData)
        return;

    // À combien de “pixels” de la texture on avance pour chaque pixel d’écran :
    double step = (double)texHeight / (double)lineHeight;

    // Calcul de la position Y “initiale” dans la texture
    //  (drawStart - milieuEcran + moitiéColonne) * step
    double texPos = (drawStart - (screenHeight / 2) + (lineHeight / 2)) * step;

    // On parcourt du haut de la colonne jusqu’au bas
    for (int y = drawStart; y < drawEnd; y++)
    {
        // On mappe le Y écran -> Y de la texture
        int texY = (int)texPos & (texHeight - 1); 
        texPos += step;

        // On récupère la couleur de la texture
        unsigned int color = *(unsigned int*)(texData
            + (texY * size_line + texX * (bpp / 8)));

        // Puis on dessine le pixel (x,y) dans l’image finale
        char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
