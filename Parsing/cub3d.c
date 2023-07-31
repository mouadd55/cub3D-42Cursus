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

int	count_commas(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == ',')
			count++;
		i++;
	}
	return (count);
}

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

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!(str[i] >= '0' && str[i++] <= '9'))
			return (1);
	return (0);
}

int	*create_rgb_arr(int r, int g, int b)
{
	int	*rgb;

	if (!(r >= 0 && r < 256) || !(g >= 0 && g < 256) || !(b >= 0 && b < 256))
		return (NULL);
	rgb = malloc(4 * sizeof(int));
	if (!rgb)
		return(NULL);
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	rgb[3] = 0;
	return (rgb);
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

int	check_rgb_values(t_infos *infos)
{
	t_vars	vars;

	vars.tmp = infos;
	while (vars.tmp)
	{
		vars.i = -1;
		if (vars.tmp->element[0] == 'F' || vars.tmp->element[0] == 'C')
		{
			if (count_commas(vars.tmp->value) > 2)
				return (1);
			vars.arr = ft_split(vars.tmp->value, ',');
			while (vars.arr[++vars.i])
				if (ft_isdigit(vars.arr[vars.i])
					|| ft_strlen(vars.arr[vars.i]) > 3)
					return (1);
			vars.tmp->rgb = create_rgb_arr(ft_atoi(vars.arr[0]),
				ft_atoi(vars.arr[1]), ft_atoi(vars.arr[2]));
			if (!vars.tmp->rgb)
				return (1);
			ft_free_arr(vars.arr);
		}
		vars.tmp = vars.tmp->link;
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
	if (count.ceiling != 1 || count.floor != 1 || count.north != 1
		|| count.south != 1 || count.east != 1 || count.west != 1)
		return (1);
	if (check_rgb_values(*infos))
		return (1);
	return (0);
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
