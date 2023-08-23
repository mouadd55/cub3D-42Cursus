/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:06:11 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/23 16:54:54 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_vars *vars, double x2, double y2)
{
	double	dx;
	double	dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	vars->x1 = vars->player.p_x1;
	vars->y1 = vars->player.p_y1;
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
	x1 = x;
	y1 = y;
	while (a < 360)
	{
		x2 = x1 + cos(a * M_PI / 180) * 1.9;
		y2 = y1 + sin(a * M_PI / 180) * 1.9;
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
			{
				if (vars->y * MINIMAP_SIZE < WINDOW_HEIGHT / 2)
					draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
						+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, vars->ceiling_color);
				else
				{
					draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
						+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, vars->floor_color);
				}
			}
			else if (vars->map[vars->y][vars->x] == '1')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
					+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, 0xffffff);
			else if (vars->map[vars->y][vars->x] == '0')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE)
					+ vars->i, (vars->y * MINIMAP_SIZE) + vars->j, 0xdbd6d6);
		}
	}
}

void	calculate_next_move_of_player(t_vars *vars)
{
	double	pixels_per_step;
	if (vars->player.walk_dir_side)
	{
		pixels_per_step = vars->player.walk_dir_side * WALKING_SPEED;
		vars->player.p_x2 = vars->player.p_x1 + cos(vars->player.starting_angle + (M_PI / 2)) * pixels_per_step;
		vars->player.p_y2 = vars->player.p_y1 - sin(vars->player.starting_angle + (M_PI / 2)) * pixels_per_step;
	}
	else {
		pixels_per_step = vars->player.walk_direction * WALKING_SPEED;
		vars->player.starting_angle += vars->player.turn_direction * vars->player.rotation_speed;
		vars->player.p_x2 = vars->player.p_x1 + cos(vars->player.starting_angle) * pixels_per_step;
		vars->player.p_y2 = vars->player.p_y1 - sin(vars->player.starting_angle) * pixels_per_step;
	}
}

void	check_if_there_is_a_wall(t_vars *vars)
{
	if (vars->map[(int)floor(vars->player.p_y2 / MINIMAP_SIZE)]
		[(int)floor(vars->player.p_x2 / MINIMAP_SIZE)] != '1')
	{
		vars->player.p_x1 = vars->player.p_x2;
		vars->player.p_y1 = vars->player.p_y2;
	}
}

int	draw_minimap(t_vars *vars)
{
	vars->y = -1;
	calculate_next_move_of_player(vars);
	get_floor_and_ceiling_color(vars);
	while (vars->map && ++vars->y < vars->height)
	{
		vars->x = -1;
		while (++vars->x < vars->width && vars->map[vars->y][vars->x])
		{
			vars->j = -1;
			draw_pixels_in_each_square(vars);
		}
	}
	check_if_there_is_a_wall(vars);
	draw_circle(vars->player.p_x1, vars->player.p_y1, &vars->image);
	calculate_x2_and_y2(&vars->player);
	draw_line(vars, vars->player.x_final, vars->player.y_final);
	mlx_clear_window(vars->mlx, vars->mlx_win);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
	return (0);
}
