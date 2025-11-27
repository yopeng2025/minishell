#include "minishell.h"

static int	strdup_node(char **array, size_t i, t_list *node)
{
	array[i] = ft_strdup(node->str);
	if (!array[i])
		return (0);
	return (1);
}

char	**list_to_array(t_list *env)
{
	char	**array;
	t_list	*list;
	size_t	i;
	size_t	len;

	list = env;
	len = len_list(list);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	if (!strdup_node(array, i, list))
		return (NULL);
	i++;
	list = list->next;
	while (list != env && i < len)
	{
		if (!strdup_node(array, i, list))
			return (NULL);
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

void	swap_array(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

void	sort_array(char **array, t_list *env)
{
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = len_list(env);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(array[i], array[j], INT_MAX) > 0)
			{
				swap_array(&array[i], &array[j]);
				continue ;
			}
			j++;
		}
		i++;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free (array);
}
