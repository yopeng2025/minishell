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

void	free_token_list(t_token **head_token)
{
	t_token	*tmp;
	t_token	*curr;

	if (!head_token || !*head_token)
		return ;
	curr = *head_token;
	while (curr->next != *head_token)
	{
		tmp = curr->next;
		free(curr->str);
		free(curr);
		curr = tmp;
	}
	free(curr->str);
	free(curr);
	*head_token = NULL;
}

void	free_cmd_list(t_cmd **head_cmd)
{
	t_cmd	*tmp;
	t_cmd	*curr;

	if (!head_cmd || !*head_cmd)
		return ;
	curr = *head_cmd;
	while (curr->next != *head_cmd)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	free(curr);
	*head_cmd = NULL;
}