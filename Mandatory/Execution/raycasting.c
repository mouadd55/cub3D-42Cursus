/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:57:31 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/01 22:16:43 by bbenidar         ###   ########.fr       */
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
		&& *ray_y < vars->height * MINIMAP_SIZE
		&& *ray_x < (int)ft_strlen(vars->map[(int)*ray_y / MINIMAP_SIZE])
		* MINIMAP_SIZE)
	{
		   if (vars->ray[vars->i].up_down == UP)
            *ray_y -= 0.000001;
        if (vars->ray[vars->i].left_right == LEFT)
            *ray_x -= 0.000001;
		if (vars->map[(int)(*ray_y / MINIMAP_SIZE)]
            [(int)(*ray_x / MINIMAP_SIZE)] != '0')
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
	vars->a_y = floor(vars->player.p_y1 / MINIMAP_SIZE) * MINIMAP_SIZE;
	if (vars->ray[vars->i].up_down == DOWN)
		vars->a_y += MINIMAP_SIZE;
	vars->a_x = vars->player.p_x1
		+ (vars->a_y - vars->player.p_y1) / tan(vars->ray[vars->i].ray_angle);
	vars->ystep = MINIMAP_SIZE;
	if (vars->ray[vars->i].up_down == UP)
		vars->ystep *= -1;
	vars->xstep = vars->ystep / tan(vars->ray[vars->i].ray_angle);
	if ((vars->ray[vars->i].left_right == LEFT && vars->xstep > 0)
		|| (vars->ray[vars->i].left_right == RIGHT && vars->xstep < 0))
		vars->xstep *= -1;
	vars->ray[vars->i].horizontal_intersection_x = vars->a_x;
	vars->ray[vars->i].horizontal_intersection_y = vars->a_y;
	if (vars->ray[vars->i].up_down == UP)
		vars->ray[vars->i].horizontal_intersection_y--;
	find_first_intersection_with_wall(vars,
		&vars->ray[vars->i].horizontal_intersection_x,
		&vars->ray[vars->i].horizontal_intersection_y);
}

void	vertical_wall_intersection(t_vars *vars)
{
	what_direction_the_player_is_facing(vars);
	vars->a_x = floor(vars->player.p_x1 / MINIMAP_SIZE) * MINIMAP_SIZE;
	if (vars->ray[vars->i].left_right == RIGHT)
		vars->a_x += MINIMAP_SIZE;
	vars->a_y = vars->player.p_y1 + (vars->a_x - vars->player.p_x1)
		* tan(vars->ray[vars->i].ray_angle);
	vars->xstep = MINIMAP_SIZE;
	if (vars->ray[vars->i].left_right == LEFT)
		vars->xstep *= -1;
	vars->ystep = vars->xstep * tan(vars->ray[vars->i].ray_angle);
	if ((vars->ray[vars->i].up_down == UP && vars->ystep > 0)
		|| (vars->ray[vars->i].up_down == DOWN && vars->ystep < 0))
		vars->ystep *= -1;
	vars->ray[vars->i].vertical_intersection_x = vars->a_x;
	vars->ray[vars->i].vertical_intersection_y = vars->a_y;
	if (vars->ray[vars->i].left_right == LEFT)
		vars->ray[vars->i].vertical_intersection_x--;
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

void	draw_rays(t_vars *vars, int horizontal_distance, int vertical_distance)
{
	if (horizontal_distance < vertical_distance)
	{
		vars->ray[vars->i].wallhit_x = vars->ray[vars->i].horizontal_intersection_x;
		vars->ray[vars->i].wallhit_y = vars->ray[vars->i].horizontal_intersection_y;
		vars->ray[vars->i].distance = horizontal_distance;
		vars->ray[vars->i].was_hit_v = 0;
	}
	else
	{
		vars->ray[vars->i].wallhit_x = vars->ray[vars->i].vertical_intersection_x;
		vars->ray[vars->i].wallhit_y = vars->ray[vars->i].vertical_intersection_y;
		vars->ray[vars->i].distance = vertical_distance;
		vars->ray[vars->i].was_hit_v = 1;
	}
}

void rgb(int red, int green, int blue, int *color) {
    *color = (red << 16) | (green << 8) | blue;
}

void ft_texture(t_vars *vars)
{
    void *img_ptr;
    void *img_ptr2;
    int bits_per_pixel;
    int endian;
    
    img_ptr = mlx_xpm_file_to_image(vars->mlx, "/Users/bbenidar/Desktop/mybranch/Mandatory/Parsing/test.xpm", &vars->xpm_width, &vars->xpm_height);
    if(!img_ptr)
	{
		
		perror("img : ");
		return ;
	}
	img_ptr2 = mlx_xpm_file_to_image(vars->mlx, "/Users/bbenidar/Desktop/mybranch/Mandatory/Parsing/test2.xpm", &vars->xpm_width2, &vars->xpm_height2);
    vars->image.text_img = mlx_get_data_addr(img_ptr, &bits_per_pixel, &vars->image.size_line, &endian);
	if(!vars->image.text_img)
	{
		printf("errsor");
		return ;
	}
	vars->image.text_img2 = mlx_get_data_addr(img_ptr2, &bits_per_pixel, &vars->image.size_line2, &endian);
	if(!vars->image.text_img)
	{
		printf("errsor");
		return ;
	}
	printf("xpm_width = %d | xpm_height = %d\n", vars->xpm_width, vars->xpm_height);

}

void	rendering_walls(t_vars *vars)
{
	double rect_y1;
	double rect_y2;
	double projected_wall_height;
	vars->i = -1;
	while (++vars->i < WINDOW_WIDTH)
	{
		double corect_wall_dis = vars->ray[vars->i].distance
		* cos(vars->ray[vars->i].ray_angle - vars->player.starting_angle);
		projected_wall_height = fabs((64 / corect_wall_dis)
				* ((WINDOW_WIDTH / 2) / tan(vars->fov_angle / 2)));
		rect_y1 = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
		rect_y2 = rect_y1 + projected_wall_height;
		// double  intencity = 100 / corect_wall_dis;
		double offsetx;
		// offsetx *= 64 / 64;
			// rgb( vars->red, vars->green, vars->blue - (vars->blue / 2), &color);
		// double intencity = vars->ray[vars->i].was_hit_v;
		// rgb( vars->red*intencity, vars->green*intencity, bl, &color);
		double top =  rect_y1;
			if(vars->ray[vars->i].was_hit_v == 1)
			{
				offsetx = fmod(vars->ray[vars->i].wallhit_y * vars->xpm_width / 64 , vars->xpm_width);
			}
				// rgb( vars->red, vars->green, vars->blue, &color);
			else
			{
				// printf("vertical_intersection_x = %f\n", vars->ray[vars->i].vertical_intersection_x);
				offsetx = fmod(vars->ray[vars->i].wallhit_x * vars->xpm_width2 / 64 , vars->xpm_width2);
			}
		while (rect_y1 < rect_y2)
		{
			// int idx = 
			unsigned int color;
			if(vars->ray[vars->i].was_hit_v == 1)
			{
				double offse_y = (rect_y1 - top) * ((float)vars->xpm_height / projected_wall_height);
				color = draw_pixels_image(&vars->image, offsetx, offse_y, vars->ray[vars->i].was_hit_v);

			}
				// rgb( vars->red, vars->green, vars->blue, &color);
			else
			{
				double offse_y = (rect_y1 - top) * ((float)vars->xpm_height2 / projected_wall_height);
				color = draw_pixels_image(&vars->image, offsetx, offse_y, vars->ray[vars->i].was_hit_v);
			}
			// printf("offsetx = %d | offset_y = %d\n", offsetx, offse_y);
			// char *pixl = (vars->image.text_img + (((int)offsetx * (4)) + ((int)offse_y * vars->image.size_line)));
			// color = *(unsigned int*)pixl;
			// printf("color = %d\n", color);
				draw_pixels_on_image(&vars->image, vars->i, rect_y1, color);
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
		horizontal_distance = fabs(vars->player.p_x1
				- vars->ray[vars->i].horizontal_intersection_x)
			/ fabs(cos(vars->ray[vars->i].ray_angle));
		vars->ray[vars->i].ray_angle = ray_angle;
		draw_rays(vars, horizontal_distance, vertical_distance);
		ray_angle += vars->fov_angle / WINDOW_WIDTH;
	}
	rendering_walls(vars);
}
