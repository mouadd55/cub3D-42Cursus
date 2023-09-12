/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:06:11 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/12 15:37:05 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * draw_line - This function draws a line between two points defined by
 *  'vars->x1', 'vars->y1' (starting point) and 'x2', 'y2' (ending point)
 *  with the specified 'color' on the image.
 * @vars: A pointer to a struct containing image data and line coordinates.
 * @x2: The x-coordinate of the ending point of the line.
 * @y2: The y-coordinate of the ending point of the line.
 * @color: An integer representing the color of the line to be drawn.
*/
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
	while (++vars->j < WALL_SIZE * 0.2)
	{
		vars->i = -1;
		while (++vars->i < WALL_SIZE * 0.2)
		{
			if (vars->map[vars->y][vars->x] == '1')
				draw_pixels_on_image(&vars->image, vars->x * WALL_SIZE * 0.2
					+ vars->i, (vars->y * WALL_SIZE * 0.2)
					+ vars->j, 0x525b56);
			else if (vars->map[vars->y][vars->x] == '0')
				draw_pixels_on_image(&vars->image, vars->x * WALL_SIZE * 0.2
					+ vars->i, (vars->y * WALL_SIZE * 0.2)
					+ vars->j, 0xa4978e);
		}
	}
}

int	draw_minimap(t_vars *vars)
{
	calculate_next_move_of_player(vars);
	get_floor_and_ceiling_color(vars);
	if (wall_collision(vars) == 0)
	{
		vars->player.p_x1 = vars->player.p_x2;
		vars->player.p_y1 = vars->player.p_y2;
	}
	initialize_rays_infos(vars);
	calculate_ending_point_coordinates_of_player_line(&vars->player);
	mlx_clear_window(vars->mlx, vars->mlx_win);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
	mlx_string_put(vars->mlx, vars->mlx_win, 450, 700, 0x111,
		"+: increase player speed   -: decrease player speed");
	return (0);
}
