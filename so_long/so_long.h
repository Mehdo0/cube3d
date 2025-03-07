/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:13:54 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/07 16:46:25 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define IMG_W 32
# define IMG_H 32
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UARROW 126
# define LARROW 123
# define DARROW 125
# define RARROW 124
# define UP -1
# define DOWN 1
# define LEFT -1
# define RIGHT 1

//strcture pour gerer la map le jeu et les textures

typedef struct s_img
{
	void	*player_1;
	void	*player_2;
	void	*player_3;
	void	*background;
}				t_img;

typedef struct s_map
{
	char	**map;
	void	*object;
	int		x;
	int		y;
	int		diamonds;
}				t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	int		p_x;
	int		p_y;
	int		counter;
	int		collected;
	t_map	*map;
	t_img	*img;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_vars;

//********************/

int			file_read(const char *f_name, char **carte, t_map *map);
int			ft_exit(t_data *data);
int			ft_line_length(int fd);
int			ft_count_lines(int fd, int line_length, int img_w);
int			ft_key_hook(int keycode, t_data *data);
int			file_read(const char *f_name, char **carte, t_map *map);
void		ft_window_size(t_data *data, char **argv);
void		ft_create_map(t_data *data);
void		exit_error(void);
void		ft_parse_input(t_data *data, char **argv, int argc);
void		ft_win(t_data *data);
void		ft_check_valid_path(t_data *data);
void		fill_map(FILE *fichier, char **carte);
void		ft_init(t_data *data, t_map *map);
void		ft_move(t_data *data, char pos, int dir);
void		ft_put_background(t_data *data);
void		start_menu(void *mlx);
void		ft_map_error(char *error_msg);
void		ft_put_object(t_data *data, char *relative_path);
void		ft_put_player(t_data *data);
t_map		*init_map(void);

#endif