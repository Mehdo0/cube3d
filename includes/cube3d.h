/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:34 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/07 11:24:47 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "../libft/libft.h"

# include <stdlib.h>
# include <stdio.h>

typedef struct s_player
{
    float	x;
    float	y;
    float	dir;
    float	fov;
}    t_player;

#endif