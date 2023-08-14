/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:46:38 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/14 17:32:45 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_wall(char **str, int i, int j)
{
	if(j == 0)
		return (0);
	else if (str[i][j + 1] == ' ' || str[i][j - 1] == ' ' || str[i + 1][j] == ' ' || str[i - 1][j] == ' ')
		return (0);
	else if (str[i][j + 1] == '\0' || str[i][j - 1] == '\0' || str[i + 1][j] == '\0' || str[i - 1][j] == '\0')
		return (0);
	return (1);
}

int	ft_count_elem(char **str)
{
	int		 i;
	int		 j;
	static int  count;

	i = 0;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'S'
				|| str[i][j] == 'E' || str[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	printf("%d\n", count);
	if (count > 1 || count == 0)
		return (0);
	return (1);
}

int ft_check_map(char **str)
{
	int i;
	int j;

	i = 0;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if (str[i][j] != ' ' && str[i][j] != '1' && str[i][j] != '0'
				&& str[i][j] != 'N' && str[i][j] != 'S'
				&& str[i][j] != 'E' && str[i][j] != 'W')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	general_map_check(char **map)
{
	int i;
	int j;

	i = 0;
	if (!ft_count_elem(map) || !ft_check_map(map))
		return (ft_bben_error(2) ,0);
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W' ) && !check_wall(map, i, j))
				return (ft_bben_error(1) ,0);
			j++;
		}
		i++;
	}
	return (1);
}
