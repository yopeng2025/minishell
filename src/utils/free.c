#include "minishell.h"

void	free_all(t_data *data, char *err, int ext)
{
	if (err)
		print_error(err);
	if (data->env)
		free_list(&data->env);
	if (data->token)
		free_token_list(&data->token);
	if (data->cmd)
		free_cmd_list(&data->cmd);
	if (data->pip[0] && data->pip[0] != -1)
		close(data->pip[0]);
	if (data->pip[1] && data->pip[1] != -1)
		close(data->pip[1]);
	rl_clear_history();
	if (access(".heredoc.tmp", F_OK) == 0)
		unlink(".heredoc.tmp");
	if (exit != -1)
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

//之后要加close fd 和free param
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
