/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:21 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/10 10:22:06 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_pixels_on_image(t_img *img, int x, int y, int color)
{
	int		position;
	char	*pixel;

	if (x < 0 || y < 0 || y > WINDOW_HEIGHT || x > WINDOW_WIDTH)
		return ;
	position = ((x * (img->bits_per_pixel / 8)) + (y * img->line_length));
	pixel = img->addr + position;
	*(int *)pixel = color;
}

void	draw_pixels_in_each_square(t_vars *vars)
{
	while (++vars->j < MINIMAP_SIZE)
	{
		vars->i = -1;
		while (++vars->i < MINIMAP_SIZE)
		{
			if (vars->map[vars->y][vars->x] == ' ')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE) + vars->i,
				(vars->y * MINIMAP_SIZE) + vars->j, 0x000000);
			else if (vars->map[vars->y][vars->x] == '1')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE) + vars->i,
				(vars->y * MINIMAP_SIZE) + vars->j, 0xffffff);
			else if (vars->map[vars->y][vars->x] == '0'
				|| vars->map[vars->y][vars->x] == 'P')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE) + vars->i,
				(vars->y * MINIMAP_SIZE) + vars->j, 0xdbd6d6);
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
			if (vars->map[vars->y][vars->x] == 'P')
			{
				draw_circle(vars->player.x, vars->player.y, &vars->image);
				calculate_x2_and_y2(&vars->player);
				draw_line(vars, vars->player.x_final, vars->player.y_final);	
			}
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

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free_data(&vars->infos, NULL, vars->map);
	free (vars);
	exit(0);
}

void	init_player_infos(t_vars *v)
{
	v->j = -1;
	while (++v->j < v->height)
	{
		v->i = -1;
		while (++v->i < v->width && v->map[v->j][v->i])
		{
			if (v->map[v->j][v->i] == 'N' || v->map[v->j][v->i] == 'W'
				|| v->map[v->j][v->i] == 'S' || v->map[v->j][v->i] == 'E')
				break ;
		}
		if (v->map[v->j][v->i] == 'N' || v->map[v->j][v->i] == 'W'
			|| v->map[v->j][v->i] == 'S' || v->map[v->j][v->i] == 'E')
			break ;
	}
	v->player.x = v->i * MINIMAP_SIZE;
	v->player.y = v->j * MINIMAP_SIZE;
	if (v->map[v->j][v->i] == 'N')
		v->player.starting_angle = M_PI / 2;
	else if (v->map[v->j][v->i] == 'W')
		v->player.starting_angle = M_PI;
	else if (v->map[v->j][v->i] == 'E')
		v->player.starting_angle = 2 * M_PI;
	else if (v->map[v->j][v->i] == 'S')
		v->player.starting_angle = 3 * M_PI / 2;
	v->map[v->j][v->i] = 'P';
}

void	open_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	get_window_resolution(vars);
	vars->mlx_win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!vars->mlx_win)
		exit(1);
	vars->image.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
		&vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	init_player_infos(vars);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
}
