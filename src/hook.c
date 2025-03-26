/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:04:24 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/26 16:48:42 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	dites_oui_aux_hook(int key, t_env *env)
{
	(void)env;
	if (key == 65307)
		exit(0);
	return (0);
}

int	close_window(t_env *env)
{
	if (env->config)
	{
		ft_free_config(env->config);
		free(env->config);
	}
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	exit(0);
	return (0);
}

void	handle_hook(t_env *env)
{
	mlx_key_hook(env->win, dites_oui_aux_hook, env);
	mlx_hook(env->win, 17, 0, close_window, env);
}

int	key_press(int keycode, t_env *env)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 13 || keycode == 119)
		env->keys.up = 1;
	else if (keycode == 1 || keycode == 115)
		env->keys.down = 1;
	else if (keycode == 0 || keycode == 100)
		env->keys.strafe_left = 1;
	else if (keycode == 2 || keycode == 97)
		env->keys.strafe_right = 1;
	else if (keycode == 123 || keycode == 65363)
		env->keys.left = 1;
	else if (keycode == 124 || keycode == 65361)
		env->keys.right = 1;
	else if (keycode == 53 || keycode == 65307)
		close_window(env);
	else if (keycode == 49 || keycode == 32)
		env->keys.action = 1;
	return (0);
}

int	key_release(int keycode, t_env *env)
{
	if (keycode == 13 || keycode == 119)
		env->keys.up = 0;
	else if (keycode == 1 || keycode == 115)
		env->keys.down = 0;
	else if (keycode == 0 || keycode == 100)
		env->keys.strafe_left = 0;
	else if (keycode == 2 || keycode == 97)
		env->keys.strafe_right = 0;
	else if (keycode == 123 || keycode == 65363)
		env->keys.left = 0;
	else if (keycode == 124 || keycode == 65361)
		env->keys.right = 0;
	else if (keycode == 49 || keycode == 32)
		env->keys.action = 0;
	return (0);
}

int mouse_move(int x, int y, t_env *env)
{
    static int last_x = -1;  // Stocke la dernière position x connue
    float sensitivity = 0.005; // Ajuste la sensibilité de la souris

    // Pour la première détection, on initialise last_x
    if (last_x == -1)
        last_x = x;

    // Calcul de la différence de position sur l'axe x
    int dx = x - last_x;

    // Si le déplacement horizontal est nul, pas besoin de mettre à jour
    if (dx == 0)
        return (0);

    // Calcul de l'angle de rotation (en radians)
    float angle = dx * sensitivity;

    // Rotation de la direction du joueur
    float oldDirX = env->config->player.dirX;
    env->config->player.dirX = env->config->player.dirX * cos(angle) - env->config->player.dirY * sin(angle);
    env->config->player.dirY = oldDirX * sin(angle) + env->config->player.dirY * cos(angle);

    // Rotation du plan de caméra (pour le raycasting)
    float oldPlaneX = env->config->player.planeX;
    env->config->player.planeX = env->config->player.planeX * cos(angle) - env->config->player.planeY * sin(angle);
    env->config->player.planeY = oldPlaneX * sin(angle) + env->config->player.planeY * cos(angle);

    last_x = x; // Met à jour la dernière position x connue

    // On peut ignorer y dans cet exemple si l'on ne souhaite pas gérer la rotation verticale
    (void)y;
    return (0);
}
