#include "minishell.h"

void	free_all(t_data *data, char *err, int ext)
{
	if (err)
		print_error(err);
	if (data->env)
		free_list(&data->env);
	exit(ext);
}

int	free_list(t_list **env)
{
	t_list	*tmp;
	t_list	*current;

	current = *env;
	while (current->next != *env)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	free(current->str);
	free(current);
	*env = NULL;
	return (0);
}
