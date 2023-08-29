/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:14:02 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/28 17:20:46 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_if_there_is_a_wall(t_vars *vars)
{
	if ((vars->map[(int)floor((vars->player.p_y2) / MINIMAP_SIZE)]
			[(int)floor((vars->player.p_x2) / MINIMAP_SIZE)] != '1'))
	{
		vars->player.p_x1 = vars->player.p_x2;
		vars->player.p_y1 = vars->player.p_y2;
	}
}

void	calculate_next_move_of_player(t_vars *vars)
{
	double	pixels_per_step;

	if (vars->player.walk_dir_side)
	{
		pixels_per_step = vars->player.walk_dir_side * WALKING_SPEED;
		vars->player.starting_angle += vars->player.turn_direction
			* vars->player.rotation_speed;
		adjust_angles(&vars->player.starting_angle);
		vars->player.p_x2 = vars->player.p_x1 + cos(vars->player.starting_angle
				+ (M_PI / 2)) * pixels_per_step;
		vars->player.p_y2 = vars->player.p_y1 + sin(vars->player.starting_angle
				+ (M_PI / 2)) * pixels_per_step;
	}
	else
	{
		pixels_per_step = vars->player.walk_direction * WALKING_SPEED;
		vars->player.starting_angle += vars->player.turn_direction
			* vars->player.rotation_speed;
		adjust_angles(&vars->player.starting_angle);
		vars->player.p_x2 = vars->player.p_x1
			+ cos(vars->player.starting_angle) * pixels_per_step;
		vars->player.p_y2 = vars->player.p_y1
			+ sin(vars->player.starting_angle) * pixels_per_step;
	}
}

void	find_player_position(t_vars *v)
{
	v->j = -1;
	while (++v->j < v->height)
	{
		v->i = -1;
		while (++v->i < v->width && v->map[v->j][v->i])
		{
			if (v->map[v->j][v->i] == 'N' || v->map[v->j][v->i] == 'W'
				|| v->map[v->j][v->i] == 'S' || v->map[v->j][v->i] == 'E')
				break ;
		}
		if (v->map[v->j][v->i] == 'N' || v->map[v->j][v->i] == 'W'
			|| v->map[v->j][v->i] == 'S' || v->map[v->j][v->i] == 'E')
			break ;
	}
}

void	calculate_next_position_coordinates(t_player *player)
{
	int	hypotenuse;

	hypotenuse = (MINIMAP_SIZE * 0.2) / 2;
	player->x_final = (player->p_x1)
		+ (cos(player->starting_angle) * hypotenuse);
	player->y_final = (player->p_y1)
		+ (sin(player->starting_angle) * hypotenuse);
}

void	init_player_infos(t_vars *vars)
{
	find_player_position(vars);
	vars->player.walk_dir_side = 0;
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
	if (vars->map[vars->j][vars->i] == 'N')
		vars->player.starting_angle = 3 * M_PI_2;
	else if (vars->map[vars->j][vars->i] == 'W')
		vars->player.starting_angle = M_PI;
	else if (vars->map[vars->j][vars->i] == 'E')
		vars->player.starting_angle = 2 * M_PI;
	else if (vars->map[vars->j][vars->i] == 'S')
		vars->player.starting_angle = M_PI_2;
	vars->player.rotation_speed = (M_PI / 180) * 2;
	vars->player.p_x1 = vars->i * MINIMAP_SIZE + MINIMAP_SIZE / 2;
	vars->player.p_y1 = vars->j * MINIMAP_SIZE + MINIMAP_SIZE / 2;
	vars->map[vars->j][vars->i] = '0';
}
