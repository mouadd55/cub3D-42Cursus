/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_rendring_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:10:09 by bbenidar          #+#    #+#             */
/*   Updated: 2023/09/12 23:46:43 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

unsigned int	get_pixel_color(t_vars *vars,
			int offsetx, double projected_wall_height)
{
	double			offse_y;

	offse_y = (vars->line_y1 - vars->top)
		* ((float)vars->xpm_height / projected_wall_height);
	return (draw_pixels_image(&vars->image, offsetx, offse_y, 1));
}

void	color_set(t_vars *vars, unsigned int *color, int offsetx)
{
	if (vars->ray[vars->i].up_down == UP
		&& !vars->ray[vars->i].was_hit_v)
		*color = get_pixel_color(vars, offsetx, vars->projected_wall_height);
	else if (vars->ray[vars->i].up_down == DOWN
		&& !vars->ray[vars->i].was_hit_v)
		*color = get_pixel_color(vars, offsetx, vars->projected_wall_height);
	else if (vars->ray[vars->i].left_right == LEFT
		&& vars->ray[vars->i].was_hit_v)
		*color = get_pixel_color(vars, offsetx, vars->projected_wall_height);
	else if (vars->ray[vars->i].left_right == RIGHT
		&& vars->ray[vars->i].was_hit_v)
		*color = get_pixel_color(vars, offsetx, vars->projected_wall_height);
}

void	rendering_walls(t_vars *vars)
{
	unsigned int	color;

	vars->i = -1;
	while (++vars->i < WINDOW_WIDTH)
	{
		vars->correct_wall_height = vars->ray[vars->i].distance
			* cos(vars->ray[vars->i].ray_angle - vars->player.starting_angle);
		vars->projected_wall_height = (WALL_SIZE / vars->correct_wall_height)
			* ((WINDOW_WIDTH / 2) / tan(vars->fov_angle / 2));
		vars->line_y1 = (WINDOW_HEIGHT / 2) - (vars->projected_wall_height / 2);
		vars->line_y2 = vars->line_y1 + vars->projected_wall_height;
		vars->top = vars->line_y1;
		if (vars->ray[vars->i].was_hit_v == 1)
			vars->offsetx = fmod(vars->ray[vars->i].wallhit_y
					* vars->xpm_width / 64, vars->xpm_width);
		else
			vars->offsetx = fmod(vars->ray[vars->i].wallhit_x
					* vars->xpm_width2 / 64, vars->xpm_width2);
		while (vars->line_y1 < vars->line_y2)
		{
			color_set(vars, &color, vars->offsetx);
			draw_pixels_on_image(&vars->image, vars->i, vars->line_y1, color);
			vars->line_y1++;
		}
	}
}
