/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:21 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/13 19:21:43 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	create_new_image(t_vars *vars)
{
	vars->image.img = mlx_new_image(vars->mlx, vars->width
			* MINIMAP_SIZE, vars->height * MINIMAP_SIZE);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
			&vars->image.bits_per_pixel, &vars->image.line_length,
			&vars->image.endian);
}

void	open_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	get_window_resolution(vars);
	vars->mlx_win = mlx_new_window(vars->mlx, vars->width * MINIMAP_SIZE,
			vars->height * MINIMAP_SIZE, "Cub3D");
	if (!vars->mlx_win)
		exit(1);
	create_new_image(vars);
	init_player_infos(vars);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
}
