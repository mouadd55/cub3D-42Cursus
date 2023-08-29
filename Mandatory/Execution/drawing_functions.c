/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:06:11 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/28 17:20:30 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_vars *vars, double x2, double y2, int color)
{
	double	dx;
	double	dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	vars->x1 = vars->player.p_x1 * 0.2;
	vars->y1 = vars->player.p_y1 * 0.2;
	dx = x2 - vars->x1;
	dy = y2 - vars->y1;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x2 = 0;
	while (x2++ <= steps)
	{
		draw_pixels_on_image(&vars->image,
			(int)round(vars->x1), (int)round(vars->y1), color);
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
	x1 = x;
	y1 = y;
	while (a < 360)
	{
		x2 = x1 + cos(a * M_PI / 180) * 1;
		y2 = y1 + sin(a * M_PI / 180) * 1;
		draw_pixels_on_image(img, x2, y2, 0xB85042);
		a++;
	}
}

void	draw_pixels_on_image(t_img *img, int x, int y, int color)
{
	int		position;
	char	*pixel;

	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH)
		return ;
	position = ((x * (img->bits_per_pixel / 8)) + (y * img->line_length));
	pixel = img->addr + position;
	*(int *)pixel = color;
}

void	draw_pixels_in_each_square(t_vars *vars)
{
	while (++vars->j < MINIMAP_SIZE * 0.2)
	{
		vars->i = -1;
		while (++vars->i < MINIMAP_SIZE * 0.2)
		{
			if (vars->map[vars->y][vars->x] == '1')
				draw_pixels_on_image(&vars->image, vars->x * MINIMAP_SIZE * 0.2
					+ vars->i, (vars->y * MINIMAP_SIZE * 0.2)
					+ vars->j, 0x525b56);
			else if (vars->map[vars->y][vars->x] == '0')
				draw_pixels_on_image(&vars->image, vars->x * MINIMAP_SIZE * 0.2
					+ vars->i, (vars->y * MINIMAP_SIZE * 0.2)
					+ vars->j, 0xa4978e);
		}
	}
}

int	draw_minimap(t_vars *vars)
{
	vars->y = -1;
	calculate_next_move_of_player(vars);
	get_floor_and_ceiling_color(vars);
	check_if_there_is_a_wall(vars);
	initialize_rays_infos(vars);
	calculate_next_position_coordinates(&vars->player);
	while (vars->map && ++vars->y < vars->height)
	{
		vars->x = -1;
		while (++vars->x < vars->width && vars->map[vars->y][vars->x])
		{
			vars->j = -1;
			draw_pixels_in_each_square(vars);
		}
	}
	draw_line(vars, vars->player.x_final * 0.2,
		vars->player.y_final * 0.2, 12079170);
	draw_circle(vars->player.p_x1 * 0.2, vars->player.p_y1 * 0.2, &vars->image);
	mlx_clear_window(vars->mlx, vars->mlx_win);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
	return (0);
}
