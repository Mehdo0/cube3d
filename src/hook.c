/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:04:24 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/17 22:48:24 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int dites_oui_aux_hook(int key, t_env *env)
{
	(void)env;
	//printf("%d\n", key);
	if (key == 65307)
		exit(0);
	return (0);
}

int close_window(t_env *env)
{
    // Libérer les ressources allouées
    if (env->config)
    {
        ft_free_config(env->config);
        free(env->config);
    }
    
    // Détruire la fenêtre
    if (env->win)
        mlx_destroy_window(env->mlx, env->win);
    
    // Terminer MLX
    if (env->mlx)
    {
        mlx_destroy_display(env->mlx);
        free(env->mlx);
    }
    
    // Quitter le programme
    exit(0);
    return (0);
}

void	handle_hook(t_env *env)
{
	mlx_key_hook(env->win, dites_oui_aux_hook, env);
	mlx_hook(env->win, 17, 0, close_window, NULL);
}

int key_press(int keycode, t_env *env)
{
    if (keycode == 13 || keycode == 119) // W ou flèche haut
        env->keys.up = 1;
    else if (keycode == 1 || keycode == 115) // S ou flèche bas
        env->keys.down = 1;
    else if (keycode == 0 || keycode == 97) // A ou flèche gauche
        env->keys.left = 1;
    else if (keycode == 2 || keycode == 100) // D ou flèche droite
        env->keys.right = 1;
    else if (keycode == 53 || keycode == 65307) // Esc
        exit(0);
    return (0);
}

int key_release(int keycode, t_env *env)
{
    if (keycode == 13 || keycode == 119)
        env->keys.up = 0;
    else if (keycode == 1 || keycode == 115)
        env->keys.down = 0;
    else if (keycode == 0 || keycode == 97)
        env->keys.left = 0;
    else if (keycode == 2 || keycode == 100)
        env->keys.right = 0;
    return (0);
}