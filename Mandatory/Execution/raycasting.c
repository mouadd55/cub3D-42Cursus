/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:57:31 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/30 16:46:39 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	what_direction_the_player_is_facing(t_vars *vars)
{
	if (vars->ray[vars->i].ray_angle < M_PI)
		vars->ray[vars->i].up_down = DOWN;
	if (vars->ray[vars->i].ray_angle < M_PI_2
		|| vars->ray[vars->i].ray_angle > (3 * M_PI_2))
		vars->ray[vars->i].left_right = RIGHT;
}

void	find_first_intersection_with_wall(t_vars *vars,
	double *ray_x, double *ray_y)
{
	while (*ray_x >= 0
		&& *ray_y >= 0
		&& *ray_y < vars->height * WALL_SIZE
		&& *ray_x < (int)ft_strlen(vars->map[(int)(*ray_y / WALL_SIZE)])
		* WALL_SIZE)
	{
		if (vars->ray[vars->i].up_down == UP)
			*ray_y -= 0.000001;
		if (vars->ray[vars->i].left_right == LEFT)
			*ray_x -= 0.000001;
		if (vars->map[(int)(*ray_y / WALL_SIZE)]
			[(int)(*ray_x / WALL_SIZE)] != '0')
			{
				
			if (vars->ray[vars->i].up_down == UP)
				*ray_y += 0.0001;
			if (vars->ray[vars->i].left_right == LEFT)
				*ray_x += 0.0001;
				break ;
			}
		else
		{
			*ray_x += vars->xstep;
			*ray_y += vars->ystep;
		}
	}
}

/*
 * a_x and vars->a_y are the coordinates of
 * the first horizontal intersection point
*/
void	horizontal_wall_intersection(t_vars *vars)
{
	what_direction_the_player_is_facing(vars);
	vars->a_y = (int)floor(vars->player.p_y1 / WALL_SIZE) * WALL_SIZE;
	if (vars->ray[vars->i].up_down == DOWN)
		vars->a_y += WALL_SIZE;
	vars->a_x = vars->player.p_x1
		+ (vars->a_y - vars->player.p_y1) / tan(vars->ray[vars->i].ray_angle);
	vars->ystep = WALL_SIZE;
	if (vars->ray[vars->i].up_down == UP)
		vars->ystep *= -1;
	vars->xstep = vars->ystep / tan(vars->ray[vars->i].ray_angle);
	vars->ray[vars->i].horizontal_intersection_x = vars->a_x;
	vars->ray[vars->i].horizontal_intersection_y = vars->a_y;
	// if (vars->ray[vars->i].up_down == UP)
	// 	vars->ray[vars->i].horizontal_intersection_y--;
	find_first_intersection_with_wall(vars,
		&vars->ray[vars->i].horizontal_intersection_x,
		&vars->ray[vars->i].horizontal_intersection_y);
}

void	vertical_wall_intersection(t_vars *vars)
{
	what_direction_the_player_is_facing(vars);
	vars->a_x = floor(vars->player.p_x1 / WALL_SIZE) * WALL_SIZE;
	if (vars->ray[vars->i].left_right == RIGHT)
		vars->a_x += WALL_SIZE;
	vars->a_y = vars->player.p_y1 + ((vars->a_x - vars->player.p_x1)
		* tan(vars->ray[vars->i].ray_angle));
	vars->xstep = WALL_SIZE;
	if (vars->ray[vars->i].left_right == LEFT)
		vars->xstep *= -1;
	vars->ystep = vars->xstep * tan(vars->ray[vars->i].ray_angle);
	vars->ray[vars->i].vertical_intersection_x = vars->a_x;
	vars->ray[vars->i].vertical_intersection_y = vars->a_y;
	// if (vars->ray[vars->i].left_right == LEFT)
	// 	vars->ray[vars->i].vertical_intersection_x--;
	find_first_intersection_with_wall(vars,
		&vars->ray[vars->i].vertical_intersection_x,
		&vars->ray[vars->i].vertical_intersection_y);
}

void	adjust_angles(double *ray_angle)
{
	*ray_angle = fmod(*ray_angle, 2 * M_PI);
	if (*ray_angle < 0)
		*ray_angle += (2 * M_PI);
}

void	get_ray_distance(t_vars *vars, double horizontal_distance,
	double vertical_distance)
{
	if (horizontal_distance < vertical_distance)
		vars->ray[vars->i].distance = horizontal_distance;
	else
		vars->ray[vars->i].distance = vertical_distance;
}

void	rendering_walls(t_vars *vars)
{
	double	rect_y1;
	double	rect_y2;
	double	correct_wall_height;
	double	projected_wall_height;

	vars->i = -1;
	while (++vars->i < WINDOW_WIDTH)
	{
		correct_wall_height = vars->ray[vars->i].distance
			* cos(vars->ray[vars->i].ray_angle - vars->player.starting_angle);
		projected_wall_height = (WALL_SIZE / correct_wall_height)
				* ((WINDOW_WIDTH / 2) / tan(vars->fov_angle / 2));
		rect_y1 = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
		rect_y2 = rect_y1 + projected_wall_height;
		while (rect_y1 < rect_y2)
		{
			draw_pixels_on_image(&vars->image, vars->i, rect_y1, 4463901);
			rect_y1++;
		}
	}
}

void	initialize_rays_infos(t_vars *vars)
{
	double	ray_angle;
	double	vertical_distance;
	double	horizontal_distance;

	vars->i = -1;
	vars->fov_angle = 60 * (M_PI / 180);
	ray_angle = vars->player.starting_angle - (vars->fov_angle / 2);
	while (++vars->i < WINDOW_WIDTH)
	{
		vars->ray[vars->i].up_down = UP;
		vars->ray[vars->i].left_right = LEFT;
		adjust_angles(&ray_angle);
		vertical_wall_intersection(vars);
		horizontal_wall_intersection(vars);
		vertical_distance = fabs(vars->player.p_x1
				- vars->ray[vars->i].vertical_intersection_x)
			/ fabs(cos(vars->ray[vars->i].ray_angle));
		horizontal_distance = fabs(vars->player.p_x1 - vars->ray[vars->i].horizontal_intersection_x)
			/ fabs(cos(vars->ray[vars->i].ray_angle));
		vars->ray[vars->i].ray_angle = ray_angle;
		get_ray_distance(vars, horizontal_distance, vertical_distance);
		ray_angle += vars->fov_angle / WINDOW_WIDTH;
	}
	rendering_walls(vars);
}
