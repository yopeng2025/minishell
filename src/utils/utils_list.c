#include "minishell.h"

size_t	len_list(t_list *list)
{
	t_list	*tmp;
	size_t	i;

	if ((list))
	{
		i = 1;
		tmp = list;
		while (tmp->next != list)
		{
			i++;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

static int	list_new_elem_str(t_list **new, char *str)
{
	(*new) = malloc(sizeof(t_list));
	if (*new == NULL)
		return (0);
	(*new)->str = str;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

static void	add_first(t_list **list, t_list *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	append(t_list **list, char *str)
{
	t_list	*new;

	list_new_elem_str(&new, str);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}
