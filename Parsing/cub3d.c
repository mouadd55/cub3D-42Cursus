/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:38:45 by moudrib           #+#    #+#             */
/*   Updated: 2023/07/31 13:26:49 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_print(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > 32)
			return (1);
		i++;
	}
	return (0);
}

int	count_elements(t_vars *vars, t_counter *count)
{
	while (vars->tmp)
	{
		if (ft_strlen(vars->tmp->element) > 2)
			return (1);
		if (!ft_strcmp(vars->tmp->element, "C"))
			count->ceiling++;
		else if (!ft_strcmp(vars->tmp->element, "F"))
			count->floor++;
		else if (!ft_strcmp(vars->tmp->element, "NO"))
			count->north++;
		else if (!ft_strcmp(vars->tmp->element, "SO"))
			count->south++;
		else if (!ft_strcmp(vars->tmp->element, "WE"))
			count->west++;
		else if (!ft_strcmp(vars->tmp->element, "EA"))
			count->east++;
		vars->tmp = vars->tmp->link;
	}
	return (0);
}

int	check_missing_ar_duplicated_element(t_infos **infos, t_vars vars)
{
	t_counter	count;

	count.east = 0;
	count.west = 0;
	count.north = 0;
	count.south = 0;
	count.floor = 0;
	count.ceiling = 0;
	vars.tmp = *infos;
	if (count_elements(&vars, &count))
		return (1);
	if (count.ceiling == 1 && count.floor == 1 && count.north == 1
		&& count.south == 1 && count.east == 1 && count.west == 1)
		return (0);
	return (1);
}

void	check_if_informations_are_valid(char **elements)
{
	t_vars	vars;
	t_infos	*infos;

	vars.i = -1;
	infos = NULL;
	while (elements[++vars.i])
	{
		vars.j = 0;
		vars.arr = ft_split(elements[vars.i], ' ');
		while (vars.arr[vars.j])
			vars.j++;
		if (vars.j > 2)
			ft_error(5, &infos, elements, vars.arr);
		else
			ft_lstadd_back(&infos, ft_lstnew(ft_strdup(vars.arr[0]),
					ft_strdup(vars.arr[1])));
		ft_free_arr(vars.arr);
	}
	if (check_missing_ar_duplicated_element(&infos, vars))
		ft_error(5, 0, 0, 0);
	ft_free_arr(elements);
	while (infos)
	{
		printf("element: %3s -- value: %s\n", infos->element, infos->value);
		infos = infos->link;
	}
	// ft_destroy_list(&infos);
}

void	read_file_and_get_informations(char *file_path)
{
	t_vars	vars;
	char	*line;

	vars.map_fd = open(file_path, O_RDONLY);
	if (vars.map_fd < 0)
		ft_error(4, 0, 0, 0);
	vars.elements = malloc(7 * sizeof(char *));
	if (!vars.elements)
		return ;
	line = ft_get_next_line(vars.map_fd);
	vars.i = 0;
	while (line)
	{
		if (is_print(line) && vars.i < 6)
			vars.elements[vars.i++] = ft_substr(line, 0, ft_strlen(line) - 1);
		if (vars.i == 6)
		{
			vars.elements[vars.i] = 0;
			free (line);
			break ;
		}
		free(line);
		line = ft_get_next_line(vars.map_fd);
	}
	check_if_informations_are_valid(vars.elements);
}

void	leaks()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	// atexit(leaks);
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (0);
	if (ac < 2)
		ft_error(1, 0, 0, 0);
	else if (ac > 2)
		ft_error(2, 0, 0, 0);
	if (check_valid_extension(av[1]))
		ft_error(3, 0, 0, 0);
	read_file_and_get_informations(av[1]);
	free(vars);
}
