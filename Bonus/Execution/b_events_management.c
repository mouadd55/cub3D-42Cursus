/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_events_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:07:05 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/12 23:48:36 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == 13 || keycode == 1)
		vars->player.walk_direction = FALSE;
	else if (keycode == 0 || keycode == 2)
		vars->player.side_walk = FALSE;
	else if (keycode == 123 || keycode == 124)
		vars->player.turn_direction = FALSE;
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	else if (keycode == 124)
		vars->player.turn_direction = RIGHT;
	else if (keycode == 123)
		vars->player.turn_direction = LEFT;
	else if (keycode == 13)
		vars->player.walk_direction = FORWARD;
	else if (keycode == 1)
		vars->player.walk_direction = BACKWARD;
	else if (keycode == 0)
		vars->player.side_walk = LEFT;
	else if (keycode == 2)
		vars->player.side_walk = RIGHT;
	else if (keycode == 69)
	{
		if (vars->speed < 7)
			vars->speed++;
	}
	else if (keycode == 78)
	{
		if (vars->speed > 1)
			vars->speed--;
	}
	else if (keycode == 12)
	{
		vars->hid_mouse *= -1;
		if (vars->hid_mouse == -1)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
	}
	else if (keycode == 36)
	{
		if (vars->amo > 0 && vars->woppen == PISTOL)
			vars->amo = vars->amo - 1;
		vars->fire = 1;
	}
	else if (keycode == 3)
	{
		if (vars->woppen == KNIFE)
			vars->woppen = PISTOL;
		else if (vars->woppen == PISTOL)
			vars->woppen = KNIFE;
	}
	if (keycode == 15)
	{
		if (vars->ammo_full > 0)
		{
			if (vars->amo < 30)
				vars->fire = 3;
			if ((vars->ammo_full - (30 - vars->amo) >= 0))
			{
				vars->ammo_full = vars->ammo_full - (30 - vars->amo);
				vars->amo = 30;
			}
			else
			{
				printf("ammo_full = %d\n", vars->ammo_full);
				vars->amo += vars->ammo_full;
				vars->ammo_full = 0;
			}
		}
	}
	return (0);
}
