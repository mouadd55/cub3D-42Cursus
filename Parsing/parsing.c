/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:31:19 by moudrib           #+#    #+#             */
/*   Updated: 2023/07/31 10:35:18 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(int cases)
{
	if (cases == 1)
		ft_putstr("\e[1m\x1B[31mError: \e[37mToo few arguments.\n");
	else if (cases == 2)
		ft_putstr("\e[1m\x1B[31mError: \e[37mToo many arguments.\n");
	else if (cases == 3)
		ft_putstr("\e[1m\x1B[31mError: \e[37mInvalid extension.\n");
	else if (cases == 4)
		ft_putstr("\e[1m\x1B[31mError: \e[37mFile does not exist.\n");
	exit(1);
}

int	check_valid_extension(char *file_name)
{
	int	start_of_extension;

	if (ft_strcmp(file_name, ".cub") == 0)
		return (1);
	else
	{
		start_of_extension = ft_strlen(file_name) - 4;
		if (file_name[0] != '.'
			&& ft_strcmp(file_name + start_of_extension, ".cub") == 0)
			return (0);
	}
	return (1);
}
