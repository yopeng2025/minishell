#include "minishell.h"

int	ft_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	if (!tmp)
		return (0);
	if (ft_strchr(tmp->str, '='))
		printf("%s\n", tmp->str);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (ft_strchr(tmp->str, '='))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (0);
}