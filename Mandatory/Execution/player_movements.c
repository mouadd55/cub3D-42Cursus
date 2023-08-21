/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:14:02 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/21 12:19:21 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	calculate_x2_and_y2(t_player *player)
{
	player->x_final = (int)((player->p_x1)
			+ (cos(player->starting_angle) * (MINIMAP_SIZE / 2)));
	player->y_final = (int)((player->p_y1)
			+ (-sin(player->starting_angle) * (MINIMAP_SIZE / 2)));
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	else if (keycode == 13)
	{
		vars->player.walk_direction = 1;
		vars->player.turn_direction = 0;
	}
	else if (keycode == 1)
	{
		vars->player.walk_direction = -1;
		vars->player.turn_direction = 0;
	}
	else if (keycode == 123)
	{
		vars->player.walk_direction = 0;
		vars->player.turn_direction = 1;
	}
	else if (keycode == 124)
	{
		vars->player.walk_direction = 0;
		vars->player.turn_direction = -1;
	}
	mlx_clear_window(vars->mlx, vars->mlx_win);
	draw_minimap(vars);
	return (0);
}

void	init_player_infos(t_vars *vars)
{
	find_player_position(vars);
	vars->player.turn_direction = 0;
	vars->player.walk_direction = 0;
	vars->player.walking_speed = WALKING_SPEED;
	vars->player.p_x1 = vars->i * MINIMAP_SIZE + MINIMAP_SIZE / 2;
	vars->player.p_y1 = vars->j * MINIMAP_SIZE + MINIMAP_SIZE / 2;
	vars->player.rotation_speed = ROTATION_SPEED;
	if (vars->map[vars->j][vars->i] == 'N')
		vars->player.starting_angle = M_PI / 2;
	else if (vars->map[vars->j][vars->i] == 'W')
		vars->player.starting_angle = M_PI;
	else if (vars->map[vars->j][vars->i] == 'E')
		vars->player.starting_angle = 2 * M_PI;
	else if (vars->map[vars->j][vars->i] == 'S')
		vars->player.starting_angle = 3 * M_PI / 2;
	vars->map[vars->j][vars->i] = 'P';
}
