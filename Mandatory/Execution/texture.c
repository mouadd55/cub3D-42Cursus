/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:34:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/31 16:08:44 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define TEXTURE_SIZE 64




void ft_textur(t_vars *vars)
{
    void *img_ptr;
    int bits_per_pixel;
    int endian;
    
    img_ptr = mlx_xpm_file_to_image(vars->mlx, "../xpm/test.xpm", &vars->width, &vars->height);
    if(!img_ptr)
        return ;
    vars->text_img = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &vars->size_line, &endian);
    
    
}