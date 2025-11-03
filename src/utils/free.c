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

void	free_cmd_param(char **cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param && cmd_param[i])
	{
		free(cmd_param[i]);
		i++;
	}
	if (cmd_param)
		free(cmd_param);
	cmd_param = NULL;
}

void	close_cmd_fd(t_cmd *cmd)
{
	if (cmd->infile >= 0)
		close(cmd->infile);
	cmd->infile = -2;
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	cmd->outfile = -2;
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
		close_cmd_fd(curr);
		free_cmd_param(curr->cmd_param);
		free(curr);
		curr = tmp;
	}
	close_cmd_fd(curr);
	free_cmd_param(curr->cmd_param);
	free(curr);
	*head_cmd = NULL;
}
