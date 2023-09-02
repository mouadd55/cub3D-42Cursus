/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:34:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/09/02 15:32:30 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_texture(t_vars *vars)
{
	void	*img_ptr;
	void	*img_ptr2;
	int		bits_per_pixel;
	int		endian;

	img_ptr = mlx_xpm_file_to_image(vars->mlx, "./xpm/test2.xpm",
			&vars->xpm_width, &vars->xpm_height);
	img_ptr2 = mlx_xpm_file_to_image(vars->mlx, "./xpm/test.xpm",
			&vars->xpm_width2, &vars->xpm_height2);
	if (!img_ptr || !img_ptr2)
	{
		perror("image: ");
		return ;
	}
	vars->image.text_img = mlx_get_data_addr(img_ptr,
			&bits_per_pixel, &vars->image.size_line, &endian);
	vars->image.text_img2 = mlx_get_data_addr(img_ptr2,
			&bits_per_pixel, &vars->image.size_line2, &endian);
	if (!vars->image.text_img || !vars->image.text_img2)
	{
		perror("errsor");
		return ;
	}
}

int	draw_pixels_image(t_img *img, int x, int y, int flag)
{
	int		position;
	char	*pixel;

	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH)
		return (0);
	if (flag == 1)
	{
		position = ((x * (4)) + (y * img->size_line));
		pixel = img->text_img + position;
	}
	else
	{
		position = ((x * (4)) + (y * img->size_line2));
		pixel = img->text_img2 + position;
	}
	return (*(unsigned int *)pixel);
}
