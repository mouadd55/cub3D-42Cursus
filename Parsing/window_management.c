/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:21 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/05 16:17:25 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_circle(t_vars *vars, int x, int y)
{
	int		a;
	int		x_init = (x * 30) + 5;
	int		y_init = (y * 30) + 5;
	double	x_final;
	double	y_final;

	a = 0;
	while (a < 360)
	{
		x_final = x_init + cos(a * M_PI / 180) * 3.5;
		y_final = y_init + sin(a * M_PI / 180) * 3.5;
		mlx_pixel_put(vars->mlx, vars->mlx_win, x_final, y_final, 0xff0000);
		a++;
	}
}

void	draw_pixels_in_each_square(t_vars *vars)
{
	while (++vars->j < 30)
	{
		vars->i = -1;
		while (++vars->i < 30)
		{
			if (vars->map[vars->y][vars->x] == ' ')
				mlx_pixel_put(vars->mlx, vars->mlx_win, (vars->x * 30)
					+ vars->i, (vars->y * 30) + vars->j, 0x000000);
			else if (vars->map[vars->y][vars->x] == '1')
				mlx_pixel_put(vars->mlx, vars->mlx_win, (vars->x * 30)
					+ vars->i, (vars->y * 30) + vars->j, 0xffffff);
			else if (vars->map[vars->y][vars->x] == '0'
				|| vars->map[vars->y][vars->x] == 'N')
				mlx_pixel_put(vars->mlx, vars->mlx_win, (vars->x * 30)
					+ vars->i, (vars->y * 30) + vars->j, 0xdbd6d6);
		}
	}
}

void	draw_minimap(t_vars *vars)
{
	vars->y = -1;
	while (vars->map && ++vars->y < vars->height)
	{
		vars->x = -1;
		while (++vars->x < vars->width && vars->map[vars->y][vars->x])
		{
			vars->j = -1;
			draw_pixels_in_each_square(vars);
			if (vars->map[vars->y][vars->x] == 'N'
				|| vars->map[vars->y][vars->x] == 'S'
				|| vars->map[vars->y][vars->x] == 'W'
				|| vars->map[vars->y][vars->x] == 'E')
				draw_circle(vars, vars->x, vars->y);
		}
	}
}

void	get_window_resolution(t_vars *vars)
{
	vars->width = 0;
	vars->height = 0;
	while (vars->map[vars->height])
	{
		if ((int)ft_strlen(vars->map[vars->height]) > vars->width)
			vars->width = ft_strlen(vars->map[vars->height]);
		vars->height++;
	}
}


int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	// else if (keycode == 13 || keycode == 126)
	// 	move_player(vars, -1, 0);
	// else if (keycode == 1 || keycode == 125)
	// 	move_player(vars, 1, 0);
	// else if (keycode == 0 || keycode == 123)
	// 	move_player(vars, 0, -1);
	// else if (keycode == 2 || keycode == 124)
	// 	move_player(vars, 0, 1);
	mlx_clear_window(vars->mlx, vars->mlx_win);
	draw_minimap(vars);
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free_data(&vars->infos, NULL, vars->map);
	free (vars);
	exit(0);
}


void	open_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	get_window_resolution(vars);
	// printf("height: %d -- width: %d\n", vars->height, vars->width);
	vars->mlx_win = mlx_new_window(vars->mlx, vars->width * 30, vars->height * 30, "Cub3D");
	// vars->mlx_win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!vars->mlx_win)
		exit(1);
	draw_minimap(vars);
}
