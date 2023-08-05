/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:03:57 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/05 16:16:09 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_HEIGHT 810
# define WINDOW_WIDTH 1280


# include <mlx.h>
#include <limits.h>
#include <math.h>
# include "Libft_utils/libft.h"
# include "Get_next_line/get_next_line.h"


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
	int				size;
	int				flag;
	int				length;
	int				map_fd;
	char			*str;
	char			**arr;
	char			**map;
	char			**elements;
	void			*mlx;
	void			*mlx_win;
	int				width;
	int				height;
	t_infos			*tmp;
	t_infos			*infos;
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
int			key_press(int keycode, t_vars *vars);
int			move_player(t_vars *v, int i, int j);


#endif