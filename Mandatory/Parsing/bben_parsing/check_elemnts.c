/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elemnts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:49:46 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/14 17:39:37 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_bben_error(int cases)
{
    if (cases == 1)
		ft_putstr("\e[1m\x1B[31mError: watch this https://www.youtube.com/watch?v=HSvN4LbGEKU&list=PL0sl117QbbPvqUbG9x4_RK-6S9gJWy8TP&index=2 \e[37m\n"); //Map's not sealed! Edit and retry.
    else if (cases == 2)
        ft_putstr("\e[1m\x1B[31mError: watch this : https://www.youtube.com/watch?v=HSvN4LbGEKU&list=PL0sl117QbbPvqUbG9x4_RK-6S9gJWy8TP&index=2\e[37m \n");//Elements are invalid.	
}