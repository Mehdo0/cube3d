/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:02:32 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 14:50:59 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void castRays(t_env *env)
{
    t_player *player = &env->config->player;
    t_map    *map    = &env->config->map;

    for (int x = 0; x < SCREENWIDTH; x++)
    {
        // Position "cameraX" sur le plan : de -1 (gauche) à +1 (droite)
        float cameraX = 2.0f * x / (float)SCREENWIDTH - 1.0f;

        // Direction du rayon
        float rayDirx = player->dirx   + player->planex * cameraX;
        float rayDiry = player->diry   + player->planey * cameraX;

        // Case map courante (en int)
        int mapX = (int)(player->posx);
        int mapY = (int)(player->posy);

        // Distances pour avancer «case par case» (DDA)
        float deltaDistX = (fabs(rayDirx) < 1e-8) ? 1e30 : fabs(1.0f / rayDirx);
        float deltaDistY = (fabs(rayDiry) < 1e-8) ? 1e30 : fabs(1.0f / rayDiry);

        // Calcul sideDistX / sideDistY + stepX / stepY
        int stepX, stepY;
        float sideDistX, sideDistY;
        if (rayDirx < 0)
        {
            stepX     = -1;
            sideDistX = (player->posx - mapX) * deltaDistX;
        }
        else
        {
            stepX     = 1;
            sideDistX = (mapX + 1.0f - player->posx) * deltaDistX;
        }
        if (rayDiry < 0)
        {
            stepY     = -1;
            sideDistY = (player->posy - mapY) * deltaDistY;
        }
        else
        {
            stepY     = 1;
            sideDistY = (mapY + 1.0f - player->posy) * deltaDistY;
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
            perpWallDist = (mapX - player->posx + (1 - stepX) / 2.0f) / rayDirx;
        else
            perpWallDist = (mapY - player->posy + (1 - stepY) / 2.0f) / rayDiry;

        // Calcul de la hauteur de colonne
        int lineHeight = (int)(SCREENHEIGHT / perpWallDist + 10);

        // Position en haut et en bas sur l’écran (sans la clamping encore)
        int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
        int drawEnd   =  lineHeight / 2 + SCREENHEIGHT / 2;

        // Choix de la texture selon la face touchée
        void *texture = NULL;
        if (side == 0)
        {
            // Rayon E ou W
            if (stepX > 0)
                texture = env->img_textures->wall_e; 
            else
                texture = env->img_textures->wall_w;
        }
        else
        {
            // Rayon S ou N
            if (stepY > 0)
                texture = env->img_textures->wall_s;
            else
                texture = env->img_textures->wall_n;
        }

        // Calcul de la coordonnée X sur la texture [0..TEXWIDTH-1]
        float wallX;
        if (side == 0)
            wallX = player->posy + perpWallDist * rayDiry;
        else
            wallX = player->posx + perpWallDist * rayDirx;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (float)TEXWIDTH);
        // Inversion éventuelle de la texture (pour éviter de la dessiner à l’envers)
        if ((side == 0 && rayDirx > 0) || (side == 1 && rayDiry < 0))
            texX = TEXWIDTH - texX - 1;

        // Clamping vertical (on ne redimensionne PAS, on coupe juste ce qui sort de l’écran)
        if (drawStart < 0)
            drawStart = 0;
        if (drawEnd >= SCREENHEIGHT)
            drawEnd = SCREENHEIGHT - 1;

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
    // Ajustez cette marge selon la taille de votre joueur et les dimensions du mur
    float collision_margin = 0.01f;

    // Avancer (Up)
    if (env->keys.up)
    {
        float newX = player->posx + player->dirx * moveSpeed;
        float newY = player->posy + player->diry * moveSpeed;

        // Mise à jour de X (ne teste pas newY)
        if (isFree(newX + collision_margin, player->posy, map) &&
            isFree(newX - collision_margin, player->posy, map))
        {
            player->posx = newX;
        }
        // Mise à jour de Y (ne teste pas newX)
        if (isFree(player->posx, newY + collision_margin, map) &&
            isFree(player->posx, newY - collision_margin, map))
        {
            player->posy = newY;
        }
    }

    // Reculer (Down)
    if (env->keys.down)
    {
        float newX = player->posx - player->dirx * moveSpeed;
        float newY = player->posy - player->diry * moveSpeed;

        if (isFree(newX + collision_margin, player->posy, map) &&
            isFree(newX - collision_margin, player->posy, map))
        {
            player->posx = newX;
        }
        if (isFree(player->posx, newY + collision_margin, map) &&
            isFree(player->posx, newY - collision_margin, map))
        {
            player->posy = newY;
        }
    }

    // Strafe à gauche
    if (env->keys.strafe_left)
    {
        // Vecteur perpendiculaire à la direction (tourné à gauche)
        float dirx_perp = -player->diry;
        float diry_perp =  player->dirx;
        float newX = player->posx + dirx_perp * moveSpeed;
        float newY = player->posy + diry_perp * moveSpeed;

        if (isFree(newX + collision_margin, player->posy, map) &&
            isFree(newX - collision_margin, player->posy, map))
        {
            player->posx = newX;
        }
        if (isFree(player->posx, newY + collision_margin, map) &&
            isFree(player->posx, newY - collision_margin, map))
        {
            player->posy = newY;
        }
    }

    // Strafe à droite
    if (env->keys.strafe_right)
    {
        // Vecteur perpendiculaire à la direction (tourné à droite)
        float dirx_perp =  player->diry;
        float diry_perp = -player->dirx;
        float newX = player->posx + dirx_perp * moveSpeed;
        float newY = player->posy + diry_perp * moveSpeed;

        if (isFree(newX + collision_margin, player->posy, map) &&
            isFree(newX - collision_margin, player->posy, map))
        {
            player->posx = newX;
        }
        if (isFree(player->posx, newY + collision_margin, map) &&
            isFree(player->posx, newY - collision_margin, map))
        {
            player->posy = newY;
        }
    }

    // Rotation à gauche
    if (env->keys.left)
    {
        float oldDirx = player->dirx;
        player->dirx = player->dirx * cos(rotSpeed) - player->diry * sin(rotSpeed);
        player->diry = oldDirx * sin(rotSpeed) + player->diry * cos(rotSpeed);

        float oldPlanex = player->planex;
        player->planex = player->planex * cos(rotSpeed) - player->planey * sin(rotSpeed);
        player->planey = oldPlanex * sin(rotSpeed) + player->planey * cos(rotSpeed);
    }

    // Rotation à droite
    if (env->keys.right)
    {
        float oldDirx = player->dirx;
        player->dirx = player->dirx * cos(-rotSpeed) - player->diry * sin(-rotSpeed);
        player->diry = oldDirx * sin(-rotSpeed) + player->diry * cos(-rotSpeed);

        float oldPlanex = player->planex;
        player->planex = player->planex * cos(-rotSpeed) - player->planey * sin(-rotSpeed);
        player->planey = oldPlanex * sin(-rotSpeed) + player->planey * cos(-rotSpeed);
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
    double step = (double)TEXHEIGHT / (double)lineHeight;

    // Calcul de la position Y “initiale” dans la texture
    //  (drawStart - milieuEcran + moitiéColonne) * step
    double texPos = (drawStart - (SCREENHEIGHT / 2) + (lineHeight / 2)) * step;

    // On parcourt du haut de la colonne jusqu’au bas
    for (int y = drawStart; y < drawEnd; y++)
    {
        // On mappe le Y écran -> Y de la texture
        int texY = (int)texPos & (TEXHEIGHT - 1); 
        texPos += step;

        // On récupère la couleur de la texture
        unsigned int color = *(unsigned int*)(texData
            + (texY * size_line + texX * (bpp / 8)));

        // Puis on dessine le pixel (x,y) dans l’image finale
        char *dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
