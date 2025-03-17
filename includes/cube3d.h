/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:34 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/17 14:13:01 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include <stdlib.h>
# include <stdio.h>

# define MAX_LINE 1024

typedef struct s_player
{
    float	x;
    float	y;
    float	dir;
    float	fov;
}    t_player;

typedef struct s_img
{
	void	*wall_N;
    void	*wall_W;
    void	*wall_S;
    void	*wall_E;
    void    *collectible;
    void    *door;
}				t_img;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	char	**map;
	int		map_width;
	int		map_height;
}	t_config;

/* Prototype de init.c */

t_config        *ft_init_config(void);

/* Prototype de parsing.c*/

t_config	    *ft_init_and_parse_map(const char *filename);
void	        ft_free_config(t_config *config);

/* Prototype de utils.c */

void	        ft_map_error(char *error_msg);
int             ft_isspace(char s);
char	        *ft_strtok(char *str, const char *delim);

#endif