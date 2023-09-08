/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_events_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:07:05 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/06 16:29:52 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == 13 || keycode == 1)
		vars->player.walk_direction = FALSE;
	else if (keycode == 0 || keycode == 2)
		vars->player.walk_dir_side = FALSE;
	else if (keycode == 123 || keycode == 124)
		vars->player.turn_direction = FALSE;
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	else if (keycode == 124)
		vars->player.turn_direction = LEFT;
	else if (keycode == 123)
		vars->player.turn_direction = RIGHT;
	else if (keycode == 13)
		vars->player.walk_direction = FORWARD;
	else if (keycode == 1)
		vars->player.walk_direction = BACKWARD;
	else if (keycode == 0)
		vars->player.walk_dir_side = RIGHT;
	else if (keycode == 2)
		vars->player.walk_dir_side = LEFT;
	else if (keycode == 12)
	{
		vars->hid_mouse *= -1;
		if (vars->hid_mouse == -1)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	return (0);
}
