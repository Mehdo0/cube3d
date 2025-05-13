/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:34 by kgiraud           #+#    #+#             */
/*   Updated: 2025/05/13 16:29:57 by kgiraud          ###   ########.fr       */
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

typedef struct s_img_data
{
	char	*img_data;
	int		bpp;
	int		line_length;
	int		endian;
	int		x;
	int		y;
	int		pixel;
}	t_img_data;

typedef struct s_ray
{
	float	camera_x;
	float	ray_dirx;
	float	ray_diry;
	int		map_x;
	int		map_y;
	float	delta_distx;
	float	delta_disty;
	int		step_x;
	int		step_y;
	float	side_distx;
	float	side_disty;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_wall
{
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	void	*texture;
	float	wall_x;
	int		tex_x;
}	t_wall;

typedef struct s_draw_params
{
	void	*texture;
	int		tex_x;
	int		line_height;
}	t_draw_params;

typedef struct s_line
{
	int	x;
	int	start;
	int	end;
	int	color;
}	t_line;

typedef struct s_minimap
{
	int	tile_size;
	int	width;
	int	height;
	int	start_x;
	int	start_y;
}	t_minimap;

typedef struct s_minimap_draw_params
{
	int	x;
	int	y;
	int	color;
	int	tile_size;
}	t_minimap_draw_params;

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
void		init_player(t_player *player, t_map *map);
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
void		put_pixel(t_env *env, int x, int y, unsigned int color);
void		render_ceiling(t_env *env, int ceiling_color);
void		render_floor(t_env *env, int floor_color);
void		draw_image_with_transparency(t_env *env, void *img, int pos_x,
				int pos_y);

/*
** raycast.c
*/

void		cast_rays(t_env *env);
void		move_player(t_env *env, float moveSpeed, float rotSpeed);
void		draw_vertical_line(t_env *env, t_line *line);
void		draw_textured_line(t_env *env, int x, int drawStart, int drawEnd,
				void *texture, int texX, int lineHeight);
void		init_ray(t_ray *ray, t_player *player, int x);
void		calc_step_and_side_dist(t_ray *ray, t_player *player);
void		perform_dda(t_ray *ray, t_map *map);
void		calc_wall_data(t_wall *wall, t_ray *ray, t_player *player);
void		select_texture(t_wall *wall, t_ray *ray, t_env *env);
void		calc_texture_x(t_wall *wall, t_ray *ray, t_player *player);
void		draw_wall_line(t_env *env, int x, t_wall *wall);

/*
** minimap.c
*/

void		draw_minimap(t_env *env);
void		draw_background(t_env *env, int start_x, int start_y,
				t_minimap *minimap);
void		draw_walls(t_env *env, int start_x, int start_y, int tile_size);
void		draw_player_direction(t_env *env, int px, int py, int size);
int			is_valid_screen_pos(int x, int y);
int			get_tile_color(char tile);

/*
** init_player.c
*/

int			find_player_position(t_map *map, int *x, int *y);
void		set_player_direction1(t_player *player, char direction);
void		set_player_direction2(t_player *player, char direction);

/*
** map_check.c
*/

void		map_checker(char **file);
int			array_len(char **arr);
int			is_wall(char c);
int			is_space_or_player(char c);
int			is_valid_map_char(char c);
int			check_map_chars(char **map, int height);

/*
** parsing_utils.c
*/

int			ft_parse_color(const char *str, int color[3]);
void		ft_parse_color_line(t_config *config, char *trimmed, char type);
void		ft_add_map_line(t_config *config, char *line);

/*
** player_movement.c
*/

void		handle_forward(t_player *player, t_map *map, float move_speed);
void		handle_rotation(t_player *player, float rot_speed, int direction);
void		handle_strafe(t_player *player, t_map *map, float move_speed,
				int direction);

#endif