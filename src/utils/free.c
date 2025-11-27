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
	if (ext != -1)
		exit(ext);
}

int	free_list(t_list **env)
{
	t_list	*start;
	t_list	*current;
	t_list	*next_node;

	current = *env;
	if (!current)
		return (0);
	start = *env;
	current = start->next;
	while (current != start)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}
	free(start->str);
	free(start);
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
