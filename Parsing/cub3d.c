/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:45 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/14 14:56:42 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int ac, char **av)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (0);
	if (ac < 2)
		ft_error(1);
	else if (ac > 2)
		ft_error(2);
	if (check_valid_extension(av[1]))
		ft_error(3);
}
