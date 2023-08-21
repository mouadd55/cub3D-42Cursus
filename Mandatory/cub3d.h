/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:03:57 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/21 12:20:02 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_HEIGHT 810
# define WINDOW_WIDTH 1280

# define MINIMAP_SIZE 30
# define WALKING_SPEED 3
# define ROTATION_SPEED (M_PI / 180) * 9

# include <mlx.h>
# include <math.h>
# include <limits.h>
# include "../Libft_utils/libft.h"
# include "../Get_next_line/get_next_line.h"

typedef struct s_player
{
	double		p_x1;
	double		p_y1;
	double		p_x2;
	double		p_y2;
	double		x_final;
	double		y_final;
	int			turn_direction;
	int			walk_direction;
	double		walking_speed;
	double		rotation_speed;
	double		starting_angle;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}	t_img;

typedef struct s_counter
{
	int				east;
	int				west;
	int				north;
	int				south;
	int				floor;
	int				ceiling;
}	t_counter;

typedef struct s_vars
{
	int				i;
	int				j;
	int				x;
	int				y;
	double			x1;
	double			y1;
	int				size;
	int				flag;
	int				length;
	int				map_fd;
	char			*str;
	char			**arr;
	char			**map;
	char			**elements;
	void			*mlx;
	void			*img;
	void			*mlx_win;
	int				width;
	int				height;
	t_infos			*tmp;
	t_infos			*infos;
	t_img			image;
	t_player		player;
}	t_vars;

/***************************** Parsing functions ******************************/

int			ft_isdigit(char *str);
int			is_printable(char *line);
int			count_commas(char *value);
int			check_valid_extension(char *file_name);
void		ft_error(int cases, t_infos **infos, char **elements, char **arr);

int			check_rgb_values(t_infos *infos);
int			*create_rgb_arr(int r, int g, int b);
void		check_if_informations_are_valid(t_vars *vars);
int			count_elements(t_vars *vars, t_counter *count);
void		free_data(t_infos **infos, char **elements, char **arr);
int			check_missing_or_duplicated_element(t_infos **infos, t_vars *vars);

void		open_window(t_vars *vars);
int			close_window(t_vars *vars);
int			draw_minimap(t_vars *vars);
void		init_player_infos(t_vars *v);
void		create_new_image(t_vars *vars);
int			key_press(int keycode, t_vars *vars);
void		calculate_x2_and_y2(t_player *player);
void		draw_circle(int x, int y, t_img *img);
void		draw_line(t_vars *vars, double x2, double y2);
void		draw_pixels_in_each_square(t_vars *vars);
void		draw_pixels_on_image(t_img *img, int x, int y, int color);

#endif