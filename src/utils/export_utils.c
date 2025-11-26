#include "minishell.h"

static void	add_first_export(t_list **list, t_list *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

static int	list_new_export_str(t_list **new, char *str)
{
	(*new) = malloc(sizeof(t_list));
	if (*new == NULL)
		return (0);
	(*new)->str = str;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1); 
}

int	export_append(t_list **list, char *str)
{
	t_list	*new;

	list_new_export_str(&new, str);
	if (!(*list))
		add_first_export(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}
