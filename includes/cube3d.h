/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:34 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/17 14:05:38 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include <stdlib.h>
# include <stdio.h>

typedef struct s_player
{
    float	x;
    float	y;
    float	dir;
    float	fov;
}    t_player;

typedef struct s_env
{
	void	*mlx;
	void	*win;
}    t_env;

// hook
void	handle_hook(t_env *env);

#endif