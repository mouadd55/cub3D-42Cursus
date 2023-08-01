/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:08:05 by moudrib           #+#    #+#             */
/*   Updated: 2023/08/01 13:17:47 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_infos	*ft_lstnew(char *element, char *value)
{
	t_infos	*head;

	head = (t_infos *)malloc(sizeof(t_infos));
	if (!head)
		return (NULL);
	head->element = element;
	head->value = value;
	head->link = NULL;
	return (head);
}

t_infos	*ft_lstlast(t_infos *head)
{
	if (!head)
		return (NULL);
	while (head)
	{
		if (head->link == NULL)
			return (head);
		head = head->link;
	}
	return (NULL);
}

void	ft_lstadd_back(t_infos **head, t_infos *new)
{
	t_infos	*tmp;

	if (!*head || !head)
		*head = new;
	else
	{
		tmp = ft_lstlast(*head);
		tmp->link = new;
	}
}

void	*ft_destroy_list(t_infos **head)
{
	t_infos	*tmp;

	if (!head || !*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		tmp = (*head)->link;
		free((*head)->rgb);
		free((*head)->value);
		free((*head)->element);
		free(*head);
		(*head) = tmp;
	}
	head = NULL;
	return (0);
}
