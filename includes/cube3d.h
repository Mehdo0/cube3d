/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:34 by kgiraud           #+#    #+#             */
/*   Updated: 2025/05/05 14:31:57 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# define MAX_LINE      1024
# define SCREENWIDTH   1920
# define SCREENHEIGHT  1080
# define KEY_UP        13
# define KEY_DOWN      1
# define KEY_LEFT      0
# define KEY_RIGHT     2
# define TEXHEIGHT     64
# define TEXWIDTH      64

/*
** Structures
*/

typedef struct s_player
{
	float	posx;
	float	posy;
	float	diry;
	float	planey;
	float	dirx;
	float	planex;
}				t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}				t_map;

typedef struct s_img
{
	void	*hud_img;
	void	*rifle_img;
	void	*wall_n;
	void	*wall_w;
	void	*wall_s;
	void	*wall_e;
	void	*door;
}				t_img;

typedef struct s_config
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			ceiling[3];
	t_map		map;
	t_player	player;
}				t_config;

typedef struct s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			strafe_left;
	int			strafe_right;
	int			action;
}				t_keys;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	t_config	*config;
	t_keys		keys;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_img		*img_textures;
}				t_env;

/*
** Hooks
*/

void		handle_hook(t_env *env);
int			key_press(int keycode, t_env *env);
int			key_release(int keycode, t_env *env);
int			close_window(t_env *env);
int			dites_oui_aux_hook(int key, t_env *env);
int			mouse_move(int x, int y, t_env *env);

/*
** init.c
*/

t_config	*ft_init_config(void);
void		initPlayer(t_player *player, t_map *map);
t_map		init_map(void);
void		load_textures(t_env *env);
void		create_color_textures(t_env *env);
void		init_keys(t_keys *keys);

/*
** parsing.c
*/

t_config	*ft_init_and_parse_map(const char *filename);
void		ft_free_config(t_config *config);
int			init_img_textures(t_env *env);
void		ft_check_borders(t_config *config);

/*
** utils.c
*/

void		ft_map_error(char *error_msg);
int			ft_isspace(char s);
char		*ft_strtok(char *str, const char *delim);
size_t		ft_strcspn(const char *s, const char *reject);
int			create_rgb(int r, int g, int b);

/*
** render.c
*/

int			render_frame(t_env *env);
void		render_ceiling_floor(t_env *env);
int			fps_counter(t_env *env);

/*
** raycast.c
*/

void		castRays(t_env *env);
void		movePlayer(t_env *env, float moveSpeed, float rotSpeed);
void		drawVerticalLine(t_env *env, int x, int drawStart, int drawEnd,
				int color);
void		drawTexturedLine(t_env *env, int x, int drawStart, int drawEnd,
				void *texture, int texX, int lineHeight);

/*
** minimap.c
*/

void		draw_minimap(t_env *env);

/*
** map_check.c
*/

void		map_checker(char **file);
int			array_len(char **arr);
int			is_wall(char c);
int			is_space_or_player(char c);
int			is_valid_map_char(char c);

#endif