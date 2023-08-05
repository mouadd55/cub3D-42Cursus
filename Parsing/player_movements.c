/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 12:14:02 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/05 12:26:30 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	move_player(t_vars *v, int i, int j)
{
	v->i = 0;
	while (v->map[v->i])
	{
		v->j = 0;
		while (v->map[v->i][v->j])
		{
			if (v->map[v->i][v->j] == 'N' || v->map[v->i][v->j] == 'S'
				|| v->map[v->i][v->j] == 'W' || v->map[v->i][v->j] == 'E')
			{
				if (v->map[v->i + i][v->j + j] == '0')
				{
					v->map[v->i][v->j] = '0';
					v->map[v->i + i][v->j + j] = 'N';
				}
				return (0);
			}
			v->j++;
		}
		v->i++;
	}
	return (0);
}
