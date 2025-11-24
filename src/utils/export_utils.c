#include "minishell.h"

// static char	*join_export_value(char **str)
// {
// 	char	**tmp1;
// 	char	*tmp2;
// 	char	*tmp3;
// 	char	*tmp4;
// 	char	*tmp5;

// 	tmp1 = ft_split(*str, '=');
// 	if (!tmp1)
// 		return (NULL);
// 	tmp2 = ft_strjoin("\"", ft_strchr(*str, '=') + 1);
// 	tmp3 = ft_strjoin(tmp2, "\"");
// 	tmp4 = ft_strjoin(tmp1[0], "=");
// 	tmp5 = ft_strjoin(tmp4, tmp3);
// 	free(tmp1[0]);
// 	free(tmp1[1]);
// 	free(tmp1);
// 	free(tmp2);
// 	free(tmp3);
// 	free(tmp4);
// 	free(*str);
// 	*str = tmp5;
// 	printf("[debug]new export string: %s\n", *str);
// 	return(*str);
// }

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
	// if (ft_strchr(str, '=') && (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>')))
	// 	join_export_value(&str);
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

