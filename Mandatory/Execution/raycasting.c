/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:57:31 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/27 14:16:06 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	what_direction_the_player_is_facing(t_vars *vars)
{
	if (vars->ray[vars->i].ray_angle < M_PI)
		vars->ray[vars->i].up_down = DOWN;
	if (vars->ray[vars->i].ray_angle < M_PI_2 || vars->ray[vars->i].ray_angle > (3 * M_PI_2))
		vars->ray[vars->i].left_right = RIGHT;
}

/*
 * a_x and a_y are the coordinates of the first horizontal intersection point
*/
void	horizontal_wall_intersection(t_vars *vars)
{
	double	a_x;
	double	a_y;
	double	xstep;
	double	ystep;

	what_direction_the_player_is_facing(vars);
	a_y = floor(vars->player.p_y1 / MINIMAP_SIZE) * MINIMAP_SIZE;
	if (vars->ray[vars->i].up_down == DOWN)
		a_y += MINIMAP_SIZE;
	a_x = vars->player.p_x1 + (a_y - vars->player.p_y1) / tan(vars->ray[vars->i].ray_angle);
	ystep = MINIMAP_SIZE;
	if (vars->ray[vars->i].up_down == UP)
		ystep *= -1;
	xstep = ystep / tan(vars->ray[vars->i].ray_angle);
	if ((vars->ray[vars->i].left_right == LEFT && xstep > 0) || (vars->ray[vars->i].left_right == RIGHT && xstep < 0))
		xstep *= -1;
	vars->ray[vars->i].horizontal_intersection_x = a_x;
	vars->ray[vars->i].horizontal_intersection_y = a_y;
	if (vars->ray[vars->i].up_down == UP)
		vars->ray[vars->i].horizontal_intersection_y--;
	// printf("xstep: %d\n", xstep);
	// printf("ystep: %d\n", ystep);
	// printf("ray_angle: %f\n", vars->ray[vars->i].ray_angle);
	while (vars->ray[vars->i].horizontal_intersection_x >= 0
		&& vars->ray[vars->i].horizontal_intersection_y >= 0
		&& vars->ray[vars->i].horizontal_intersection_x < (int)ft_strlen(vars->map[(int)vars->ray[vars->i].horizontal_intersection_y / MINIMAP_SIZE]) * MINIMAP_SIZE
		&& vars->ray[vars->i].horizontal_intersection_y < vars->height * MINIMAP_SIZE)
	{
		// printf("y: %d\n", vars->ray[vars->i].horizontal_intersection_y / MINIMAP_SIZE);
		// printf("x: %d\n", vars->ray[vars->i].horizontal_intersection_x / MINIMAP_SIZE);
		// printf("x: %d\n", vars->ray[vars->i].horizontal_intersection_x);
		if (vars->map[(int)vars->ray[vars->i].horizontal_intersection_y / MINIMAP_SIZE]
			[(int)vars->ray[vars->i].horizontal_intersection_x / MINIMAP_SIZE] != '0')
			break ;
		else
		{
			vars->ray[vars->i].horizontal_intersection_x += xstep;
			vars->ray[vars->i].horizontal_intersection_y += ystep;
		}
	}
	draw_pixels_on_image(&vars->image, (int)vars->ray[vars->i].horizontal_intersection_x, (int)vars->ray[vars->i].horizontal_intersection_y, 0xffffff);
}

void	vertical_wall_intersection(t_vars *vars)
{
	double	a_x;
	double	a_y;
	double	xstep;
	double	ystep;

	what_direction_the_player_is_facing(vars);
	a_x = floor(vars->player.p_x1 / MINIMAP_SIZE) * MINIMAP_SIZE;
	if (vars->ray[vars->i].left_right == RIGHT)
		a_x += MINIMAP_SIZE;
	a_y = vars->player.p_y1 + (a_x - vars->player.p_x1) * tan(vars->ray[vars->i].ray_angle);
	xstep = MINIMAP_SIZE;
	if (vars->ray[vars->i].left_right == LEFT)
		xstep *= -1;
	ystep = xstep * tan(vars->ray[vars->i].ray_angle);
	if ((vars->ray[vars->i].up_down == UP && ystep > 0) || (vars->ray[vars->i].up_down == DOWN && ystep < 0))
		ystep *= -1;
	vars->ray[vars->i].vertical_intersection_x = a_x;
	vars->ray[vars->i].vertical_intersection_y = a_y;
	if (vars->ray[vars->i].left_right == LEFT)
		vars->ray[vars->i].vertical_intersection_x--;
	// printf("xstep: %d\n", xstep);
	// printf("ystep: %d\n", ystep);
	// printf("ray_angle: %f\n", vars->ray[vars->i].ray_angle);
	while (vars->ray[vars->i].vertical_intersection_x >= 0
		&& vars->ray[vars->i].vertical_intersection_y >= 0
		&& vars->ray[vars->i].vertical_intersection_x < vars->width * MINIMAP_SIZE
		&& vars->ray[vars->i].vertical_intersection_y < vars->height * MINIMAP_SIZE)
	{
		// printf("ver_y: %f\n", (vars->ray[vars->i].vertical_intersection_y));
		// printf("y: %d\n", (int)floor((vars->ray[vars->i].vertical_intersection_y) / MINIMAP_SIZE));
		// printf("x: %d\n", (int)floor((vars->ray[vars->i].vertical_intersection_x) / MINIMAP_SIZE));
		if (vars->map[(int)vars->ray[vars->i].vertical_intersection_y / MINIMAP_SIZE]
			[(int)vars->ray[vars->i].vertical_intersection_x / MINIMAP_SIZE] != '0')
			break ;
		else
		{
			vars->ray[vars->i].vertical_intersection_x += xstep;
			vars->ray[vars->i].vertical_intersection_y += ystep;
		}
	}
	draw_pixels_on_image(&vars->image, (int)vars->ray[vars->i].vertical_intersection_x, (int)vars->ray[vars->i].vertical_intersection_y, 0xffffff);
}

void	adjust_angles(double *ray_angle)
{
	*ray_angle = fmod(*ray_angle, 2 * M_PI);
	if (*ray_angle < 0)
		*ray_angle += (2 * M_PI);
}

void	draw_rays(t_vars *vars, double ray_angle, int horizontal_distance, int vertical_distance)
{
	(void)ray_angle;
	int		hypotenuse;
	double	x2;
	double	y2;

	hypotenuse = MINIMAP_SIZE * 3;
	x2 = (vars->player.p_x1)
		+ (cos(vars->ray[vars->i].ray_angle) * hypotenuse);
	y2 = (vars->player.p_y1)
		+ (sin(vars->ray[vars->i].ray_angle) * hypotenuse);
	if (horizontal_distance <= vertical_distance)
		draw_line(vars, vars->ray[vars->i].horizontal_intersection_x, vars->ray[vars->i].horizontal_intersection_y, 12488803);
	else
		draw_line(vars, vars->ray[vars->i].vertical_intersection_x, vars->ray[vars->i].vertical_intersection_y, 12488803);
}

void	initialize_rays_infos(t_vars *vars)
{
	double	ray_angle;
	int	vertical_distance;
	int	horizontal_distance;

	vars->i = -1;
	vars->fov_angle = 60 * (M_PI / 180);
	ray_angle = vars->player.starting_angle - (vars->fov_angle / 2);
	while (++vars->i < WINDOW_WIDTH)
	{
		vars->ray[vars->i].up_down = UP;
		vars->ray[vars->i].left_right = LEFT;
		adjust_angles(&ray_angle);
		horizontal_wall_intersection(vars);
		vertical_wall_intersection(vars);
		// if (vars->ray[0].up_down == UP)
		// 	printf("Player is facing up\n");
		// else
		// 	printf("Player is facing down\n");
		// if (vars->ray[0].left_right == LEFT)
		// 	printf("Player is facing left\n");
		// else
		// 	printf("Player is facing right\n");
		vertical_distance = fabs(vars->player.p_x1 - vars->ray[vars->i].vertical_intersection_x) / fabs(cos(vars->ray[vars->i].ray_angle));
		horizontal_distance = fabs(vars->player.p_x1 - vars->ray[vars->i].horizontal_intersection_x) / fabs(cos(vars->ray[vars->i].ray_angle));
		// printf("horizontal_distance: %d\n", horizontal_distance);
		// printf("vertical_distance: %d\n", vertical_distance);
		vars->ray[vars->i].ray_angle = ray_angle;
		draw_rays(vars, ray_angle, horizontal_distance, vertical_distance);
		ray_angle += vars->fov_angle / WINDOW_WIDTH;
	}
}
