/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:14:02 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/10 10:27:15 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_x2_and_y2(t_player *player)
{
	player->x_final = (int)((player->x + (MINIMAP_SIZE / 2))
		 + (cos(player->starting_angle ) * (MINIMAP_SIZE / 2)));
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

void draw_line(t_vars *vars, int x2, int y2)
{
	double	dx;
	double	dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	vars->x1 = vars->player.x + (MINIMAP_SIZE / 2);
	vars->y1 = vars->player.y + (MINIMAP_SIZE / 2);
	dx = x2 - vars->x1;
	dy = y2 - vars->y1;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	for (int i = 0; i < steps; i++)
	{
		draw_pixels_on_image(&vars->image,
			(int)round(vars->x1), (int)round(vars->y1), 0xff0000);
		vars->x1 = vars->x1 + x_inc;
		vars->y1 = vars->y1 + y_inc;
	}
}

void draw_circle(int x, int y, t_img *img)
{
	int		a;
	int		x1;
	int		y1;
	double	x2;
	double	y2;

	a = 0;
	x1 = x + MINIMAP_SIZE / 2;
	y1 = y + MINIMAP_SIZE / 2;
	while (a < 360)
	{
		x2 = x1 + cos(a * M_PI / 180) * MINIMAP_SIZE / 11;
		y2 = y1 + sin(a * M_PI / 180) * MINIMAP_SIZE / 11;
		draw_pixels_on_image(img, x2, y2, 0xff0000);
		a++;
	}
}
