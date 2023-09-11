/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_drawing_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:06:11 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/11 16:29:37 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_pixels_on_minimap_image(t_minimap *minimap, int x, int y,
	int color)
{
	int		position;
	char	*pixel;

	if (x < 0 || y < 0 || y >= MINIMAP_HEIGHT || x >= MINIMAP_WIDTH)
		return ;
	position = ((x * (minimap->bits_per_pixel / 8))
			+ (y * minimap->line_length));
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

void	player_pistl_animation(t_vars *vars)
{
	static int count;

	if(vars->fire == 0)
	{
		if(count >= 0 && count <= 10)
		{
			vars->rec = vars->pistol_img[0];
			count++;
		}
		else if(count > 10 && count <= 20)
		{
			vars->rec = vars->pistol_img[1];
			count++;
		}
		else if(count > 20)
			count = 0;
	}
	else if(vars->fire == 1 && vars->amo > 0)
	{
		if(count >= 0 && count <= 2)
		{
			vars->rec = vars->pistol_img[1];
			count++;
		}
		else if(count > 2 && count <= 4)
		{
			vars->rec = vars->pistol_img[2];
			count++;
		}
		else if(count > 4 && count <= 6)
		{
			vars->rec = vars->pistol_img[3];
			count++;
		}
		else if(count > 6 && count <= 7)
		{
			vars->rec = vars->pistol_img[4];
			count++;
		}
		else if(count > 7 && count <= 8)
		{
			vars->rec = vars->pistol_img[5];
			count++;
		}
		else if(count > 8 && count <= 9)
		{
			vars->rec = vars->pistol_img[6];
			count++;
		}
		else if(count > 9)
		{
			vars->fire = 0;
			count = 0;
		}
	}
	else if(vars->fire == 3 && vars->ammo_full > 0)
	{
		if(count >= 0 && count <= 2)
		{
			vars->rec = vars->pistol_img[7];
			count++;
		}
		else if(count > 2 && count <= 4)
		{
			vars->rec = vars->pistol_img[8];
			count++;
		}
		else if(count > 4 && count <= 6)
		{
			vars->rec = vars->pistol_img[9];
			count++;
		}
		else if(count > 6 && count <= 8)
		{
			vars->rec = vars->pistol_img[10];
			count++;
		}
		else if(count > 8 && count <= 10)
		{
			vars->rec = vars->pistol_img[11];
			count++;
		}
		else if(count > 10 && count <= 12)
		{
			vars->rec = vars->pistol_img[12];
			count++;
		}
		else if(count > 12 && count <= 14)
		{
			vars->rec = vars->pistol_img[13];
			count++;
		}
		else if(count > 14 && count <= 16)
		{
			vars->rec = vars->pistol_img[14];
			count++;
		}
		else if(count > 16 && count <= 18)
		{
			vars->rec = vars->pistol_img[15];
			count++;
		}
		else if(count > 18 && count <= 20)
		{
			vars->rec = vars->pistol_img[16];
			count++;
		}
		else if(count > 20 && count <= 22)
		{
			vars->rec = vars->pistol_img[17];
			count++;
		}
		else if(count > 22 && count <= 24)
		{
			vars->rec = vars->pistol_img[18];
			count++;
		}
		else if(count > 24 && count <= 26)
		{
			vars->rec = vars->pistol_img[19];
			count++;
		}
		else if(count > 26 && count <= 28)
		{
			vars->rec = vars->pistol_img[20];
			count++;
		}
		else if(count > 28 && count <= 30)
		{
			vars->rec = vars->pistol_img[21];
			count++;
		}
		else if(count > 30 && count <= 32)
		{
			vars->rec = vars->pistol_img[22];
			count++;
		}
		else if(count > 32 && count <= 34)
		{
			vars->rec = vars->pistol_img[23];
			count++;
		}
		else if(count > 34 && count <= 36)
		{
			vars->rec = vars->pistol_img[24];
			count++;
		}
		else if(count > 36 && count <= 38)
		{
			vars->rec = vars->pistol_img[25];
			count++;
		}
		else if(count > 38 && count <= 40)
		{
			vars->rec = vars->pistol_img[26];
			count++;
		}
		else if(count > 40 && count <= 42)
		{
			vars->rec = vars->pistol_img[27];
			count++;
		}
		else if(count > 42 && count <= 44)
		{
			vars->rec = vars->pistol_img[28];
			count++;
		}
		else if(count > 44)
		{
			vars->fire = 0;
			count = 0;
		}
	}
}


void	player_animation(t_vars *vars)
{
	static int count;
	
	if (vars->fire == 0 || vars->fire == 3)
	{
		if(count >= 0 && count <= 4)
		{
			vars->rec = vars->knife_img[0];
			count++;
		}
		else if(count > 4 && count <= 8)
		{
			vars->rec = vars->knife_img[1];
			count++;
		}
		else if(count > 8 && count <= 12)
		{
			vars->rec = vars->knife_img[2];
			count++;
		}
		else if(count > 12 && count <= 16)
		{
			vars->rec = vars->knife_img[3];
			count++;
		}
		else if(count > 16 && count <= 20)
		{
			vars->rec = vars->knife_img[4];
			count++;
		}
		else if(count > 20)
			count = 0;
	}
	else if(vars->fire == 1)
	{
		if(count >= 0 && count <= 2)
		{
			vars->rec = vars->knife_img[0];
			count++;
		}
		else if(count > 2 && count <=4)
		{
			vars->rec = vars->knife_img[1];
			count++;
		}
		else if(count >4 && count <= 6)
		{
			vars->rec = vars->knife_img[2];
			count++;
		}
		else if(count > 6 && count <= 8)
		{
			vars->rec = vars->knife_img[3];
			count++;
		}
		else if(count > 8 && count <= 10)
		{
			vars->rec = vars->knife_img[4];
			count++;
		}
		else if(count > 10 && count <= 12)
		{
			vars->rec = vars->knife_img[5];
			count++;
		}
		else if(count > 12 && count <= 14)
		{
			vars->rec = vars->knife_img[6];
			count++;
		}
		else if(count > 14 && count <= 16)
		{
			vars->rec = vars->knife_img[7];
			count++;
		}
		else if (count > 16 && count <= 18)
		{
			vars->rec = vars->knife_img[8];
			count++;
		}
		else if(count > 18)
		{
			vars->fire = 0;
			count = 0;
		}
	}
}

void ft_get_amo(t_vars *vars)
{
	char *str;
	
	if(vars->woppen == 0)
		mlx_string_put(vars->mlx, vars->mlx_win, 550, 100, 0xFFFFFF, "amo : ∞");
	else if(vars->woppen == 1)
	{
		str = ft_strjoin(ft_strdup("amo : "), ft_itoa(vars->amo));
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, ft_itoa(vars->ammo_full));
		mlx_string_put(vars->mlx, vars->mlx_win, 550, 100, 0xFFFFFF, str); 
	}
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
	draw_circle(MINIMAP_WIDTH / 3, MINIMAP_HEIGHT / 3, &vars->minimap);
	mlx_clear_window(vars->mlx, vars->mlx_win);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win,
		vars->image.win_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win,
		vars->minimap.minimap_img, 0, 0);
	if(vars->woppen == 0)
		player_animation(vars);
	else if (vars->woppen == 1)
		player_pistl_animation(vars);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->rec, 250, 0);
	ft_get_amo(vars);
	mlx_string_put(vars->mlx, vars->mlx_win, 450, 700, 0x111, "+: increase player speed   -: decrease player speed");
	return (0);
}
