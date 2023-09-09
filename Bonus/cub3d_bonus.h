/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:03:57 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/09 16:40:16 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH 1280


# define MINIMAP_HEIGHT 150
# define MINIMAP_WIDTH 250

# define FALSE 0

# define LEFT 1
# define RIGHT -1

# define FORWARD 1
# define BACKWARD -1

# define UP 1
# define DOWN -1

# define LEFT 1
# define RIGHT -1

# define WALL_SIZE 64
# define WALKING_SPEED 6
# define ROTATION_SPEED 4

# include "../mlx/mlx.h"
# include <math.h>
# include <limits.h>
# include "Libft_utils/libft.h"
# include "Get_next_line/get_next_line.h"

typedef struct s_ray
{
	int				up_down;
	int				left_right;
	double			distance;
	double			ray_angle;
	double			vertical_intersection_x;
	double			vertical_intersection_y;
	double			wallhit_y;
	double			wallhit_x;
	int				was_hit_v;
	double			horizontal_intersection_x;
	double			horizontal_intersection_y;
}	t_ray;

typedef struct s_player
{
	double			p_x1;
	double			p_y1;
	double			p_x2;
	double			p_y2;
	double			x_final;
	double			y_final;
	int				turn_dir_top;
	int				walk_dir_side;
	int				turn_direction;
	int				walk_direction;
	double			rotation_speed;
	double			starting_angle;
}	t_player;

typedef struct s_minimap
{
	void			*minimap_img;
	char			*minimap_addr;
	int				endian;
	int				line_length;
	int				bits_per_pixel;
}	t_minimap;

typedef struct s_img
{
	void			*img;
	char			*no_img;
	char			*we_img;
	char			*so_img;
	char			*ea_img;
	int				no_line;
	int				we_line;
	int				so_line;
	int				ea_line;
	char			*addr;
	int				endian;
	int				line_length;
	int				bits_per_pixel;
	int				bits_p_pixel;
	void			*win_img;
	void 			*win_addr;
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
	int 			hid_mouse;
	int				y;
	int				size;
	int				flag;
	int				length;
	int				width;
	int				height;
	int				map_fd;
	int				floor_color;
	int				ceiling_color;
	char			*str;
	char			**arr;
	char			**map;
	char			**elements;
	void			*mlx;
	void			*img;
	void			*mlx_win;
	int				xpm_width;
	int				xpm_height;
	int				xpm_width2;
	int				xpm_height2;
	char			*img_no;
	char			*img_we;
	char			*img_so;
	char			*img_ea;
	double			x1;
	double			y1;
	double			a_x;
	double			a_y;
	double			xstep;
	double			ystep;
	double			fov_angle;
	t_infos			*tmp;
	t_img			image;
	t_infos			*infos;
	t_player		player;
	t_ray			ray[WINDOW_WIDTH];
	t_minimap		minimap;
	void			*rec;

}	t_vars;

/***************************** Parsing functions ******************************/

void		first_checks(int ac);
int			ft_isdigit(char *str);
int			ft_tablen(char **str);
int			is_printable(char *line);
int			count_commas(char *value);
int			general_map_check(char **map);
int			check_wall(char **str, int i, int j);
int			check_valid_extension(char *file_name);
void		ft_error(int cases, t_infos **infos, char **elements, char **arr);
void		ft_texture(t_vars *vars);
int			draw_pixels_image(t_img *img, int x, int y, int flag);

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
void		adjust_angles(double *ray_angle);
void		initialize_rays_infos(t_vars *vars);
int			key_press(int keycode, t_vars *vars);
int			key_release(int keycode, t_vars *vars);
int			check_if_there_is_a_wall(t_vars *vars, int x, int y);
void		draw_pixels_in_each_square(t_vars *vars);
void		get_floor_and_ceiling_color(t_vars *vars);
void		get_colors_values_from_file(t_vars *vars);
void		get_floor_and_ceiling_color(t_vars *vars);
void		calculate_next_move_of_player(t_vars *vars);
void		draw_circle(int x, int y, t_minimap *minimap);
void		calculate_next_position_coordinates(t_player *player);
void		draw_line(t_vars *vars, double x2, double y2, int color);
void		draw_pixels_on_image(t_img *img, int x, int y, int color);

int			wall_collision(t_vars *vars);
void		vertical_wall_intersection(t_vars *vars);
void		horizontal_wall_intersection(t_vars *vars);
void		find_first_intersection_with_wall(t_vars *vars, double *ray_x,
				double *ray_y);
void		what_direction_the_player_is_facing(t_vars *vars);
#endif