/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:57:31 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/24 17:50:11 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_rays(t_vars *vars)
{
	int		hypotenuse;
	double	x2;
	double	y2;

	hypotenuse = MINIMAP_SIZE * 3;
	x2 = (vars->player.p_x1)
			+ (cos(vars->ray[vars->i].ray_angle) * hypotenuse);
	y2 = (vars->player.p_y1)
			- (sin(vars->ray[vars->i].ray_angle) * hypotenuse);
	draw_line(vars, x2, y2, 12488803);
}

void	initialize_rays_infos(t_vars *vars)
{

	double	ray_angle;

	vars->i = -1;
	vars->fov_angle = 60 * (M_PI / 180);
	ray_angle = vars->player.starting_angle - (vars->fov_angle / 2);
	while (++vars->i < WINDOW_WIDTH)
	{
		vars->ray[vars->i].ray_angle = ray_angle;
		draw_rays(vars);
		ray_angle += vars->fov_angle / WINDOW_WIDTH;
	}
}
