/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:06:11 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/10 15:07:12 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_vars *vars, int x2, int y2)
{
	double	dx;
	double	dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	vars->x1 = vars->player.x + (MINIMAP_SIZE / 2);
	vars->y1 = vars->player.y + (MINIMAP_SIZE / 2);
	dx = x2 - vars->x1;
	dy = y2 - vars->y1;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x2 = 0;
	while (x2++ < steps)
	{
		draw_pixels_on_image(&vars->image,
			(int)round(vars->x1), (int)round(vars->y1), 0xff0000);
		vars->x1 = vars->x1 + x_inc;
		vars->y1 = vars->y1 + y_inc;
	}
}

void	draw_circle(int x, int y, t_img *img)
{
	int		a;
	int		x1;
	int		y1;
	double	x2;
	double	y2;

	a = 0;
	x1 = x + MINIMAP_SIZE / 2;
	y1 = y + MINIMAP_SIZE / 2;
	while (a < 360)
	{
		x2 = x1 + cos(a * M_PI / 180) * MINIMAP_SIZE / 11;
		y2 = y1 + sin(a * M_PI / 180) * MINIMAP_SIZE / 11;
		draw_pixels_on_image(img, x2, y2, 0xff0000);
		a++;
	}
}

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
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
					+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, 0x000000);
			else if (vars->map[vars->y][vars->x] == '1')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
					+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, 0xffffff);
			else if (vars->map[vars->y][vars->x] == '0'
				|| vars->map[vars->y][vars->x] == 'P')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
					+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, 0xdbd6d6);
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
