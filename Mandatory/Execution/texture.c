/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:34:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/09/03 16:22:23 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		if (tmp->element[0] == 'N' && tmp->element[1] == 'O')
			vars->img_no = ft_strdup(tmp->value);
		if (tmp->element[0] == 'S' && tmp->element[1] == 'O')
			vars->img_we = ft_strdup(tmp->value);
		if (tmp->element[0] == 'S' && tmp->element[1] == 'O')
			vars->img_so = ft_strdup(tmp->value);
		if (tmp->element[0] == 'E' && tmp->element[1] == 'A')
			vars->img_ea = ft_strdup(tmp->value);
		tmp = tmp->link;
	}
	remove_spaces(vars->img_no);
	remove_spaces(vars->img_we);
	remove_spaces(vars->img_so);
	remove_spaces(vars->img_ea);
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
	
	if (!vars->image.no_img || !vars->image.we_img)
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
		position = ((x * (4)) + (y * img->no_line));
		pixel = img->no_img + position;
	}
	else
	{
		position = ((x * (4)) + (y * img->we_line));
		pixel = img->we_img + position;
	}
	return (*(unsigned int *)pixel);
}
