/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elemnts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:49:46 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/14 17:48:16 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_bben_error(int cases)
{
    if (cases == 1)
		ft_putstr("\e[1m\x1B[31mError: \e[37mMap's not sealed! Edit and retry.\nif ur login is moudrib dzeb watch this: \nhttps://www.youtube.com/watch?v=GX51XM8igT0\n"); //Map's not sealed! Edit and retry.
    else if (cases == 2)
        ft_putstr("\e[1m\x1B[31mError: \e[37mElements are invalid. \nif ur login is moudrib dzeb watch this : \nhttps://www.youtube.com/watch?v=GX51XM8igT0 \n");//Elements are invalid.	
}