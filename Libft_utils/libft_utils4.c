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
		free((*head)->element);
		if ((*head)->value)
			free((*head)->value);
		free(*head);
		(*head) = tmp;
	}
	head = NULL;
	return (0);
}
