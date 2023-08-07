/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:21 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/07 18:20:32 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_pixels_on_image(t_img *img, int x, int y, int color)
{
	int		position;
	char	*pixel;

	if (x < 0 || y < 0 || y > WINDOW_HEIGHT || x > WINDOW_WIDTH)
	{
		printf("draw_pixels_on_image\n"); // 
		return ;
	}
	position = ((x * (img->bits_per_pixel / 8)) + (y * img->line_length));
	pixel = img->addr + position;
	*(int *)pixel = color;
}

void draw_line(double x1, double y1, int x2, int y2, t_img *img)
{
	double		dx;
	double 	dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	printf("dx: %f -- dy: %f\n", fabs(dx) , fabs(dy));
	printf("#x_inc: %f -- y_inc: %f#\n", x_inc, y_inc);
	for (int i = 0; i < steps; i++)
	{
		printf("|x1: %d -- y1: %d|\n", (int)round(x1), (int)round(x2));
		draw_pixels_on_image(img, (int)round(x1), (int)round(y1), 0xff0000);
		x1 = x1 + x_inc;
		y1 = y1 + y_inc;
	}
}

void draw_circle(int x, int y, t_img *img)
{
	int		a;
	int		x_init = (x * MINIMAP_SIZE) + 15;
	int		y_init = (y * MINIMAP_SIZE) + 15;
	double	x_final;
	double	y_final;

	a = 0;
	while (a < 360)
	{
		x_final = x_init + cos(a * M_PI / 180) * 3.5;
		y_final = y_init + sin(a * M_PI / 180) * 3.5;
		draw_pixels_on_image(img, x_final, y_final, 0xff0000);
		a++;
	}
}

void	draw_pixels_in_each_square(t_vars *vars)
{
	while (++vars->j < MINIMAP_SIZE)
	{
		vars->i = -1;
		while (++vars->i < MINIMAP_SIZE)
		{
			if (vars->map[vars->y][vars->x] == ' ')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE) + vars->i,
				(vars->y * MINIMAP_SIZE) + vars->j, 0x000000);
			else if (vars->map[vars->y][vars->x] == '1')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE) + vars->i,
				(vars->y * MINIMAP_SIZE) + vars->j, 0xffffff);
			else if (vars->map[vars->y][vars->x] == '0'
				|| vars->map[vars->y][vars->x] == 'P')
				draw_pixels_on_image(&vars->image, (vars->x * MINIMAP_SIZE) + vars->i,
				(vars->y * MINIMAP_SIZE) + vars->j, 0xdbd6d6);
		}
	}
}

void	calculate_x2_and_y2(t_player *player)
{
	player->x_final = (int)((player->x * MINIMAP_SIZE + (MINIMAP_SIZE / 2)) +
		(cos(player->starting_angle ) * (MINIMAP_SIZE / 2)));
	player->y_final = (int)((player->y * MINIMAP_SIZE + (MINIMAP_SIZE / 2)) +
		(-sin(player->starting_angle) * (MINIMAP_SIZE / 2)));
}

void	draw_minimap(t_vars *vars)
{
	vars->y = -1;
	while (vars->map && ++vars->y < vars->height)
	{
		vars->x = -1;
		while (++vars->x < vars->width && vars->map[vars->y][vars->x])
		{
			vars->j = -1;
			draw_pixels_in_each_square(vars);
			if (vars->map[vars->y][vars->x] == 'P')
			{
				vars->player.x = vars->x;
				vars->player.y = vars->y;
				printf("%f\n", vars->player.starting_angle);
				printf("vars->x: %d -- vars->y: %d\n", vars->x * MINIMAP_SIZE, vars->y * MINIMAP_SIZE + 15);
				draw_circle(vars->x, vars->y, &vars->image);
				calculate_x2_and_y2(&vars->player);
				printf("^x_final: %d -- y_final: %d^\n", vars->player.x_final, vars->player.y_final);
				draw_line(vars->x * MINIMAP_SIZE + 15, vars->y * MINIMAP_SIZE + 15,
					vars->player.x_final, vars->player.y_final, &vars->image);
					
			}
		}
	}
}

void	get_window_resolution(t_vars *vars)
{
	vars->width = 0;
	vars->height = 0;
	while (vars->map[vars->height])
	{
		if ((int)ft_strlen(vars->map[vars->height]) > vars->width)
			vars->width = ft_strlen(vars->map[vars->height]);
		vars->height++;
	}
}


int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	else if (keycode == 0)
	{
		vars->player.starting_angle += (M_PI / 180) * 2;
	}
	else if (keycode == 2)
		vars->player.starting_angle -= (M_PI / 180) * 2;
	// else if (keycode == 13 || keycode == 126)
	// 	move_player(vars, -1, 0);
	// else if (keycode == 1 || keycode == 125)
	// 	move_player(vars, 1, 0);
	// else if (keycode == 0 || keycode == 123)
	// 	move_player(vars, 0, -1);
	// else if (keycode == 2 || keycode == 124)
	// 	move_player(vars, 0, 1);
	mlx_clear_window(vars->mlx, vars->mlx_win);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free_data(&vars->infos, NULL, vars->map);
	free (vars);
	exit(0);
}

void	init_player_infos(t_vars *v)
{
	v->j = -1;
	v->flag = 0;
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

void	open_window(t_vars *vars)
{
	// t_img		img;
	// t_player	player;

	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	get_window_resolution(vars);
	vars->mlx_win = mlx_new_window(vars->mlx, vars->width * 30, vars->height * 30, "Cub3D");
	if (!vars->mlx_win)
		exit(1);
	vars->image.img = mlx_new_image(vars->mlx, vars->width * 30, vars->height * 30);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
		&vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	// printf("img: %p -- addr: %p", vars->image.img, vars->image.addr);
	init_player_infos(vars);
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->image.img, 0, 0);
}
