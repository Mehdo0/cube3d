/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:26:20 by kgiraud          #+#    #+#             */
/*   Updated: 2025/05/13 15:26:20 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	is_free(float x, float y, t_map *map)
{
	return (map->grid[(int)y][(int)x] == '0');
}

void	handle_forward(t_player *player, t_map *map, float move_speed)
{
	float	new_x;
	float	new_y;
	float	margin;

	margin = 0.01f;
	new_x = player->posx + player->dirx * move_speed;
	new_y = player->posy + player->diry * move_speed;
	if (is_free(new_x + margin, player->posy, map)
		&& is_free(new_x - margin, player->posy, map))
		player->posx = new_x;
	if (is_free(player->posx, new_y + margin, map)
		&& is_free(player->posx, new_y - margin, map))
		player->posy = new_y;
}

void	handle_rotation(t_player *player, float rot_speed, int direction)
{
	float	old_dirx;
	float	old_planex;
	float	angle;

	angle = rot_speed * direction;
	old_dirx = player->dirx;
	player->dirx = player->dirx * cos(angle) - player->diry * sin(angle);
	player->diry = old_dirx * sin(angle) + player->diry * cos(angle);
	old_planex = player->planex;
	player->planex = player->planex * cos(angle) - player->planey * sin(angle);
	player->planey = old_planex * sin(angle) + player->planey * cos(angle);
}

void	handle_strafe(t_player *player, t_map *map,
		float move_speed, int direction)
{
	float	new_x;
	float	new_y;
	float	margin;
	float	dirx_perp;
	float	diry_perp;

	margin = 0.01f;
	dirx_perp = direction * -player->diry;
	diry_perp = direction * player->dirx;
	new_x = player->posx + dirx_perp * move_speed;
	new_y = player->posy + diry_perp * move_speed;
	if (is_free(new_x + margin, player->posy, map)
		&& is_free(new_x - margin, player->posy, map))
		player->posx = new_x;
	if (is_free(player->posx, new_y + margin, map)
		&& is_free(player->posx, new_y - margin, map))
		player->posy = new_y;
}

void	move_player(t_env *env, float move_speed, float rot_speed)
{
	t_player	*player;
	t_map		*map;

	player = &env->config->player;
	map = &env->config->map;
	if (env->keys.up)
		handle_forward(player, map, move_speed);
	if (env->keys.down)
		handle_forward(player, map, -move_speed);
	if (env->keys.strafe_left)
		handle_strafe(player, map, move_speed, -1);
	if (env->keys.strafe_right)
		handle_strafe(player, map, move_speed, 1);
	if (env->keys.left)
		handle_rotation(player, rot_speed, 1);
	if (env->keys.right)
		handle_rotation(player, rot_speed, -1);
}
