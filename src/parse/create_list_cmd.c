#include "minishell.h"

bool	create_new_command(t_cmd **new)
{
	(*new) = malloc(sizeof(t_cmd));
	if (!*new)
		return (false);
	(*new)->cmd_param = NULL;
	(*new)->infile = -2;
	(*new)->outfile = -2;
	(*new)->skip_cmd = false;
	(*new)->prev = NULL;
	(*new)->next = NULL;
	return (true);
}

bool	add_command_node(t_cmd **head_cmd)
{
	t_cmd	*new;
	t_cmd	*tmp;

	if (!create_new_command(&new))
		return (false);
	if (!*head_cmd)
	{
		*head_cmd = new;
		new->prev = *head_cmd;
		new->next = *head_cmd;
	}
	else
	{
		tmp = (*head_cmd)->prev;
		tmp->next = new;
		new->prev = tmp;
		new->next = *head_cmd;
		(*head_cmd)->prev = new;
	}
	return (true);
}

bool	get_in_out_file(t_token *tmp, t_data *data)
{
	if (tmp->type == INPUT || tmp->type == HEREDOC)
	{
		if (!get_in(tmp, data->cmd->prev, data))
		{
			if (data->cmd->prev->outfile >= 0)
				close(data->cmd->outfile);
			if (data->cmd->prev->infile == -1)
				data->cmd->prev->skip_cmd =  true;
			data->cmd->prev->outfile = -1;
			return (false);
		}
	}
	else if (tmp->type == APPEND || tmp->type == TRUNCATE)
	{
		if (!get_out(tmp, data->cmd->prev, data))
		{
			if (data->cmd->prev->infile >= 0)
				close(data->cmd->infile);
			if (data->cmd->prev->outfile == -1)
				data->cmd->prev->skip_cmd =  true;
			return (false);
		}
	}
	return (true);
}

bool	fill_command(t_token *curr_token, t_data *data)
{
	t_token	*tmp;

	tmp = curr_token;
	if (!get_in_out_file(tmp, data))
		return (false);
	tmp = tmp->next;
	while (tmp->type != PIPE && tmp != data->token)
	{
		if (!get_in_out_file(tmp, data))
			return (false);
		tmp = tmp->next;
	}
	data->cmd->prev->cmd_param = get_param(data, curr_token);
	if (!data->cmd->prev->cmd_param)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (true);
}

bool	add_command(t_token *curr_token, t_data *data)
{
	if (!add_command_node(&data->cmd))
	{
		free_all(data, ERR_MALLOC, EXT_MALLOC);
		return (false);
	}
	if (!fill_command(curr_token, data) && data->cmd->skip_cmd == 0)
		return (false);
	return (true);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*curr;
	
	curr = data->token;
	if (!add_command(curr, data))
	// {
	// 	free_cmd_list(&data->cmd);
		return (false);
	// }
	curr = curr->next;
	while (curr != data->token)
	{
		if(curr->prev->type == PIPE && !add_command(curr, data))
		// {
		// 	free_cmd_list(&data->cmd);
			return (false);
		// }
		curr = curr->next;
	}
	return (true);
}
