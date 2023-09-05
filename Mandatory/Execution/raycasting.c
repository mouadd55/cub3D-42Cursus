/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:57:31 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/05 11:28:07 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	adjust_angles(double *ray_angle)
{
	*ray_angle = fmod(*ray_angle, 2 * M_PI);
	if (*ray_angle < 0)
		*ray_angle += (2 * M_PI);
}

void	what_direction_the_player_is_facing(t_vars *vars)
{
	if (vars->ray[vars->i].ray_angle < M_PI)
		vars->ray[vars->i].up_down = DOWN;
	if (vars->ray[vars->i].ray_angle < M_PI_2
		|| vars->ray[vars->i].ray_angle > (3 * M_PI_2))
		vars->ray[vars->i].left_right = RIGHT;
}

void	get_ray_distance(t_vars *vars)
{
	double	vertical_distance;
	double	horizontal_distance;

	vertical_distance = fabs(vars->player.p_x1
			- vars->ray[vars->i].vertical_intersection_x)
		/ fabs(cos(vars->ray[vars->i].ray_angle));
	horizontal_distance = fabs(vars->player.p_x1
			- vars->ray[vars->i].horizontal_intersection_x)
		/ fabs(cos(vars->ray[vars->i].ray_angle));
	if (horizontal_distance < vertical_distance)
	{
		vars->ray[vars->i].wallhit_x
			= vars->ray[vars->i].horizontal_intersection_x;
		vars->ray[vars->i].wallhit_y
			= vars->ray[vars->i].horizontal_intersection_y;
		vars->ray[vars->i].distance = horizontal_distance;
		vars->ray[vars->i].was_hit_v = 0;
	}
	else
	{
		vars->ray[vars->i].wallhit_x
			= vars->ray[vars->i].vertical_intersection_x;
		vars->ray[vars->i].wallhit_y
			= vars->ray[vars->i].vertical_intersection_y;
		vars->ray[vars->i].distance = vertical_distance;
		vars->ray[vars->i].was_hit_v = 1;
	}
}

void	rendering_walls(t_vars *vars)
{
	double			rect_y1;
	double			rect_y2;
	double			correct_wall_height;
	double			projected_wall_height;
	double			offsetx;
	double			top;
	unsigned int	color;
	double			offse_y;

	vars->i = -1;
	while (++vars->i < WINDOW_WIDTH)
	{
		correct_wall_height = vars->ray[vars->i].distance
			* cos(vars->ray[vars->i].ray_angle - vars->player.starting_angle);
		projected_wall_height = (WALL_SIZE / correct_wall_height)
			* ((WINDOW_WIDTH / 2) / tan(vars->fov_angle / 2));
		rect_y1 = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
		rect_y2 = rect_y1 + projected_wall_height;
		top = rect_y1;
		if (vars->ray[vars->i].was_hit_v == 1)
			offsetx = fmod(vars->ray[vars->i].wallhit_y
					* vars->xpm_width / 64, vars->xpm_width);
		else
			offsetx = fmod(vars->ray[vars->i].wallhit_x
					* vars->xpm_width2 / 64, vars->xpm_width2);
		while (rect_y1 < rect_y2)
		{
			if (vars->ray[vars->i].up_down == UP && !vars->ray[vars->i].was_hit_v)
			{
				//no
				offse_y = (rect_y1 - top)
					* ((float)vars->xpm_height / projected_wall_height);
				color = draw_pixels_image(&vars->image,
						offsetx, offse_y, 1);
			}
			else if (vars->ray[vars->i].up_down == DOWN && !vars->ray[vars->i].was_hit_v)
			{
				//so
				offse_y = (rect_y1 - top)
					* ((float)vars->xpm_height / projected_wall_height);
				color = draw_pixels_image(&vars->image,
						offsetx, offse_y, 3);
			}
			else if (vars->ray[vars->i].left_right == LEFT && vars->ray[vars->i].was_hit_v)
			{
				//we
				offse_y = (rect_y1 - top)
					* ((float)vars->xpm_height / projected_wall_height);
				color =  draw_pixels_image(&vars->image,
						offsetx, offse_y, 2);
			}
			else if (vars->ray[vars->i].left_right == RIGHT && vars->ray[vars->i].was_hit_v)
			{
				//ea
				offse_y = (rect_y1 - top)
					* ((float)vars->xpm_height / projected_wall_height);
				color = draw_pixels_image(&vars->image,
						offsetx, offse_y, 4);
			}
			draw_pixels_on_image(&vars->image, vars->i, rect_y1, color);
			rect_y1++;
		}
	}
}

void	initialize_rays_infos(t_vars *vars)
{
	double	ray_angle;

	vars->i = -1;
	vars->fov_angle = 60 * (M_PI / 180);
	ray_angle = vars->player.starting_angle - (vars->fov_angle / 2);
	while (++vars->i < WINDOW_WIDTH)
	{
		adjust_angles(&ray_angle);
		vars->ray[vars->i].up_down = UP;
		vars->ray[vars->i].left_right = LEFT;
		vars->ray[vars->i].ray_angle = ray_angle;
		vertical_wall_intersection(vars);
		horizontal_wall_intersection(vars);
		get_ray_distance(vars);
		ray_angle += vars->fov_angle / WINDOW_WIDTH;
	}
	rendering_walls(vars);
}
