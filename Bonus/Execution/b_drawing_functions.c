/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_drawing_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:06:11 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/08 14:20:48 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_pixels_on_minimap_image(t_minimap *minimap, int x, int y, int color)
{
	int		position;
	char	*pixel;

	if (x < 0 || y < 0 || y >= MINIMAP_HEIGHT || x >= MINIMAP_WIDTH)
		return ;
	position = ((x * (minimap->bits_per_pixel / 8)) + (y * minimap->line_length));
	pixel = minimap->minimap_addr + position;
	*(int *)pixel = color;
}

void	draw_line(t_vars *vars, double x2, double y2, int color)
{
	double	dx;
	double	dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	vars->x1 = MINIMAP_WIDTH / 3;
	vars->y1 = MINIMAP_HEIGHT / 3;
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
		draw_pixels_on_minimap_image(&vars->minimap,
			(int)round(vars->x1), (int)round(vars->y1), color);
		vars->x1 = vars->x1 + x_inc;
		vars->y1 = vars->y1 + y_inc;
	}
}

void	draw_circle(int x, int y, t_minimap *minimap)
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
		x2 = x1 + cos(a * M_PI / 180) * 4;
		y2 = y1 + sin(a * M_PI / 180) * 4;
		draw_pixels_on_minimap_image(minimap, x2, y2, 0xB85042);
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
	pixel = img->win_addr + position;
	*(int *)pixel = color;
}

void	minimap(t_vars *vars)
{
	double	start_x;
	double	start_y;

	vars->j = -1;
	start_y = vars->player.p_y1 - MINIMAP_HEIGHT;
	while (++vars->j < MINIMAP_HEIGHT * 3)
	{
		vars->i = -1;
		start_x = vars->player.p_x1 - MINIMAP_WIDTH;
		while (++vars->i < MINIMAP_WIDTH * 3)
		{
			if (start_x >= 0
				&& start_y >= 0
				&& start_x / WALL_SIZE >= 0
				&& start_y / WALL_SIZE >= 0
				&& start_y < vars->height * WALL_SIZE
				&& start_x < (int)ft_strlen(vars->map[(int)(start_y / WALL_SIZE)]) * WALL_SIZE)
			{
				if (vars->map[(int)(start_y / WALL_SIZE)][(int)(start_x / WALL_SIZE)] == '1')
					draw_pixels_on_minimap_image(&vars->minimap, (int)(vars->i / 3), (int)(vars->j / 3), 0x000000);
				else if (vars->map[(int)(start_y / WALL_SIZE)][(int)(start_x / WALL_SIZE)] == '0')
					draw_pixels_on_minimap_image(&vars->minimap, (int)(vars->i / 3), (int)(vars->j / 3), 0xa4978e);
			}
			start_x++;
		}
		start_y++;
	}
}

void	initialize_images_pointers(t_vars *vars)
{
	int	x;
	int	y;

	vars->rec = mlx_xpm_file_to_image(vars->mlx, "./xpm/Pulsar.xpm", &x, &y);
	if (!vars->rec)
		ft_error(10, 0, 0, 0);
}

int	wall_collision(t_vars *vars)
{
	if (check_if_there_is_a_wall(vars, 0, -12))
		return (1);
	else if (check_if_there_is_a_wall(vars, 0, 12))
		return (1);
	else if (check_if_there_is_a_wall(vars, -12, 0))
		return (1);
	else if (check_if_there_is_a_wall(vars, 12, 0))
		return (1);
	else if (check_if_there_is_a_wall(vars, -12, -12))
		return (1);
	else if (check_if_there_is_a_wall(vars, 12, -12))
		return (1);
	else if (check_if_there_is_a_wall(vars, -12, 12))
		return (1);
	else if (check_if_there_is_a_wall(vars, 12, 12))
		return (1);
	return (0);
}

int	draw_minimap(t_vars *vars)
{
	vars->y = -1;
	calculate_next_move_of_player(vars);
	get_floor_and_ceiling_color(vars);
	if (wall_collision(vars) == 0)
	{
		vars->player.p_x1 = vars->player.p_x2;
		vars->player.p_y1 = vars->player.p_y2;
	}
	initialize_rays_infos(vars);
	calculate_next_position_coordinates(&vars->player);
	minimap(vars);
	draw_line(vars, vars->player.x_final, vars->player.y_final, 12079170);
	draw_circle(MINIMAP_WIDTH / 3, MINIMAP_HEIGHT / 3, &vars->minimap); // draw it outside the hook
	mlx_clear_window(vars->mlx, vars->mlx_win);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.win_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->minimap.minimap_img, (WINDOW_WIDTH / 2) - (MINIMAP_WIDTH / 2), 0);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->rec, 0, 0);
	return (0);
}
