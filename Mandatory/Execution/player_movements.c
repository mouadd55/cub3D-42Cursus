/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:14:02 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/10 15:07:09 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_x2_and_y2(t_player *player)
{
	player->x_final = (int)((player->x + (MINIMAP_SIZE / 2))
			+ (cos(player->starting_angle) * (MINIMAP_SIZE / 2)));
	player->y_final = (int)((player->y + (MINIMAP_SIZE / 2))
			+ (-sin(player->starting_angle) * (MINIMAP_SIZE / 2)));
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	else if (keycode == 123)
		vars->player.starting_angle += (M_PI / 180) * 6;
	else if (keycode == 124)
		vars->player.starting_angle -= (M_PI / 180) * 6;
	else if (keycode == 13)
		vars->player.y -= 1;
	else if (keycode == 1)
		vars->player.y += 1;
	else if (keycode == 0)
		vars->player.x -= 1;
	else if (keycode == 2)
		vars->player.x += 1;
	mlx_clear_window(vars->mlx, vars->mlx_win);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
	return (0);
}

void	init_player_infos(t_vars *v)
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
	v->player.x = v->i * MINIMAP_SIZE;
	v->player.y = v->j * MINIMAP_SIZE;
	if (v->map[v->j][v->i] == 'N')
		v->player.starting_angle = M_PI / 2;
	else if (v->map[v->j][v->i] == 'W')
		v->player.starting_angle = M_PI;
	else if (v->map[v->j][v->i] == 'E')
		v->player.starting_angle = 2 * M_PI;
	else if (v->map[v->j][v->i] == 'S')
		v->player.starting_angle = 3 * M_PI / 2;
	v->map[v->j][v->i] = 'P';
}
