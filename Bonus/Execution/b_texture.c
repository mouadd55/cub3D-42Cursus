/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:34:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/09/12 14:33:35 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	remove_spaces(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] != ' ')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
}

void ft_get_name_texture(t_vars *vars)
{
	t_infos	*tmp;

	tmp = vars->infos;
	while(tmp)
	{
		if (tmp->element[0] == 'N')
			vars->img_no = tmp->value;
		if (tmp->element[0] == 'W')
			vars->img_we = tmp->value;
		if (tmp->element[0] == 'S')
			vars->img_so = tmp->value;
		if (tmp->element[0] == 'E')
			vars->img_ea = tmp->value;
		tmp = tmp->link;
	}
}

void	ft_texture(t_vars *vars)
{
	void	*no_ptr;
	void	*we_ptr;
	void	*so_ptr;
	void	*ea_ptr;
	int		bits_per_pixel;
	int		endian;
	
	ft_get_name_texture(vars);
	no_ptr = mlx_xpm_file_to_image(vars->mlx, vars->img_no,
			&vars->xpm_width, &vars->xpm_height);
	we_ptr = mlx_xpm_file_to_image(vars->mlx, vars->img_we,
			&vars->xpm_width2, &vars->xpm_height2);
	so_ptr = mlx_xpm_file_to_image(vars->mlx, vars->img_so,
			&vars->xpm_width2, &vars->xpm_height2);
	ea_ptr = mlx_xpm_file_to_image(vars->mlx, vars->img_ea,
			&vars->xpm_width2, &vars->xpm_height2);
	if (!no_ptr || !we_ptr || !so_ptr || !ea_ptr)
	{
		perror("image: ");
		return ;
	}
	vars->image.no_img = mlx_get_data_addr(no_ptr,
			&bits_per_pixel, &vars->image.no_line, &endian);
	vars->image.we_img = mlx_get_data_addr(we_ptr,
			&bits_per_pixel, &vars->image.we_line, &endian);
	vars->image.so_img = mlx_get_data_addr(so_ptr,
			&bits_per_pixel, &vars->image.so_line, &endian);
	vars->image.ea_img = mlx_get_data_addr(ea_ptr,
			&bits_per_pixel, &vars->image.ea_line, &endian);
	
	if (!vars->image.no_img || !vars->image.we_img)
	{
		perror("errsor");
		return ;
	}
}


int	draw_pixels_image(t_img *img, int x, int y, int flag, t_vars *vars)
{
	int		position;
	char	*pixel;
	
	pixel = NULL;
	position = 0;
	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH)
		return (0);
	if (flag == 1)
	{
		position = abs((x * (4)) + (y * img->no_line));
		if(position > 0 && position < vars->xpm_width * vars->xpm_height)
			pixel = img->no_img + position;
	}
	else if (flag == 2)
	{
		position = abs((x * (4)) + (y * img->we_line));
		if(position > 0 && position < vars->xpm_width * vars->xpm_height)
			pixel = img->we_img + position;
	}
	else if(flag == 3)
	{
		position = abs((x * (4)) + (y * img->so_line));
		if(position > 0 && position < vars->xpm_width * vars->xpm_height)
			pixel = img->so_img + position;
	}
	else
	{
		position = abs((x * (4)) + (y * img->ea_line));
		if(position > 0 && position <= vars->xpm_width * vars->xpm_height)
			pixel = img->ea_img + position;
	}
	return (*(unsigned int *)pixel);
}
