/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elemnts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:49:46 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/15 01:49:34 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bben_error(int cases)
{
	if (cases == 1)
		ft_putstr("\e[1m\x1B[31mError: \e[37mMap's not sealed! Edit and retry.\n");
	else if (cases == 2)
		ft_putstr("\e[1m\x1B[31mError: \e[37mElements are invalid.\n");
}

int	check_wall(char **str, int i, int j)
{
	if (j == 0)
		return (0);
	if (i == 0)
		return (0);
	else if (i == ft_tablen(str) - 1)
		return (0);
	else if (str[i][j + 1] == ' ' || str[i][j - 1] == ' '
		|| str[i + 1][j] == ' ' || str[i - 1][j] == ' ')
		return (0);
	else if (str[i][j + 1] == '\0' || str[i][j - 1] == '\0'
		|| str[i + 1][j] == '\0' || str[i - 1][j] == '\0')
		return (0);
	return (1);
}