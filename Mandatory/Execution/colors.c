/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:49:49 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/02 19:30:42 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_colors_values_from_file(t_vars *vars)
{
	t_infos	*tmp;

	tmp = vars->infos;
	while (tmp)
	{
		if (tmp->element[0] == 'C')
			vars->ceiling_color = (tmp->rgb[0] * pow(256, 2))
				+ tmp->rgb[1] * 256 + tmp->rgb[2];
		else if (tmp->element[0] == 'F')
			vars->floor_color = (tmp->rgb[0] * pow(256, 2))
				+ tmp->rgb[1] * 256 + tmp->rgb[2];
		tmp = tmp->link;
	}
}

void	get_floor_and_ceiling_color(t_vars *vars)
{
	int	ceil_grade;
	int	floor_grade;

	floor_grade = 0xA5A5A5;
	ceil_grade = vars->ceiling_color;
	get_colors_values_from_file(vars);
	vars->i = -1;
	while (++vars->i < WINDOW_HEIGHT / 2)
	{
		vars->j = -1;
		while (++vars->j < WINDOW_WIDTH)
			draw_pixels_on_image(&vars->image, vars->j, vars->i, ceil_grade);
		if (vars->i % 5 == 0)
			ceil_grade -= 0.5;
	}
	vars->i--;
	while (++vars->i < WINDOW_HEIGHT)
	{
		vars->j = -1;
		while (++vars->j < WINDOW_WIDTH)
			draw_pixels_on_image(&vars->image, vars->j, vars->i, floor_grade);
		// if (vars->i % 6 == 0)
		// 	floor_grade += (1 << 16) + (1 << 8) + 1;
	}
}
