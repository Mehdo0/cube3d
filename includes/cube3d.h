/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:34 by kgiraud           #+#    #+#             */
/*   Updated: 2025/03/24 16:11:13 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# define MAX_LINE 1024
# define screenWidth 1920
# define screenHeight 1080
# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define texHeight 64
# define texWidth 64

// Structure pour le joueur
typedef struct s_player
{
    float posX;
	float posY;
	float dirY;
	float planeY;
    float dirX;
    float planeX;
}	 t_player;

// Structure pour la carte
typedef struct s_map
{
    char	**grid;
    int		width;
	int		height;
} 	t_map;

typedef struct s_img
{
	void	*wall_N;
    void	*wall_W;
    void	*wall_S;
    void	*wall_E;
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
	t_map	map;
	t_player player;
}	t_config;

typedef struct s_keys {
    int up;            // Avancer
    int down;          // Reculer
    int left;          // Tourner à gauche
    int right;         // Tourner à droite
    int strafe_left;   // Déplacement latéral gauche
    int strafe_right;  // Déplacement latéral droit
    int action;        // Action (pour portes, etc.)
} t_keys;


typedef struct s_env
{
    void *mlx;
    void *win;
    t_config *config;
	t_keys keys;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
	t_img *img_textures;
} t_env;

// hook
void			handle_hook(t_env *env);
int 			key_press(int keycode, t_env *env);
int 			key_release(int keycode, t_env *env);
int 			close_window(t_env *env);
int 			dites_oui_aux_hook(int key, t_env *env);

/* Prototype de init.c */

t_config        *ft_init_config(void);
void            initPlayer(t_player *player, t_map *map);
t_map           init_map(void);
void			load_textures(t_env *env);
void            create_color_textures(t_env *env);
void 			init_keys(t_keys *keys);

/* Prototype de parsing.c*/

t_config	    *ft_init_and_parse_map(const char *filename);
void	        ft_free_config(t_config *config);
int	            init_img_textures(t_env *env);
void	        ft_check_borders(t_config *config);

/* Prototype de utils.c */

void	        ft_map_error(char *error_msg);
int             ft_isspace(char s);
char	        *ft_strtok(char *str, const char *delim);
size_t	        ft_strcspn(const char *s, const char *reject);
int				create_rgb(int r, int g, int b);

/* Prototype de render.c */

int             render_frame(t_env *env);
void            render_ceiling_floor(t_env *env);
int             fps_counter(t_env *env);

/* prototype de raycast.c */

void            castRays(t_env *env);
void 			movePlayer(t_env *env, float moveSpeed, float rotSpeed);
void 			drawVerticalLine(t_env *env, int x, int drawStart, int drawEnd, int color);
void            drawTexturedLine(t_env *env,
                      int x, int drawStart, int drawEnd,
                      void *texture, int texX, int lineHeight);

/* prototype de minimap.c */

void            draw_minimap(t_env *env);

#endif