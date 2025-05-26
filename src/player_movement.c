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
	int		int_x;
	int		int_y;
	char	cell;

	int_x = (int)x;
	int_y = (int)y;
	if (int_x < 0 || int_y < 0 || int_x >= map->width
		|| int_y >= map->height)
		return (0);
	if (int_x >= (int)ft_strlen(map->grid[int_y]))
		return (0);
	cell = map->grid[int_y][int_x];
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W');
}

void	handle_forward(t_player *player, t_map *map, float move_speed)
{
	float	new_x;
	float	new_y;
	float	margin;
	float	margin_x;
	float	margin_y;

	margin = 0.2f;
	new_x = player->posx + player->dirx * move_speed;
	new_y = player->posy + player->diry * move_speed;
	margin_x = margin;
	if (player->dirx <= 0)
		margin_x = -margin;
	margin_y = margin;
	if (player->diry <= 0)
		margin_y = -margin;
	if (is_free(new_x + margin_x, player->posy, map))
		player->posx = new_x;
	if (is_free(player->posx, new_y + margin_y, map))
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
	float	dx;
	float	dy;
	float	margin;

	margin = 0.3f;
	dx = direction * -player->diry * move_speed;
	dy = direction * player->dirx * move_speed;
	if (is_free(player->posx + dx, player->posy, map))
		player->posx += dx;
	if (is_free(player->posx, player->posy + dy, map))
		player->posy += dy;
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
