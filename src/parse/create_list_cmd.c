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
bool	fill_command(t_token *curr_token, t_data *data)
{
	if (!get_infile(curr_token, data->cmd->prev, data))
	{
		if (data->cmd->prev->infile != -1)
			return (false);
		data->cmd->prev->skip_cmd = true;
		data->cmd->prev->outfile = -1;
		return (true);
	}
	if (!get_outfile(curr_token, data->cmd->prev, data))
	{
		if (data->cmd->prev->outfile != -1)
		{
			if (data->cmd->prev->infile >= 0)
				close(data->cmd->infile);
			return (false);
		}
		data->cmd->prev->skip_cmd = true;
		return (true);
	}
	data->cmd->prev->cmd_param = get_param(data, curr_token);
	if (!data->cmd->prev->cmd_param)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (true);
}

bool	add_command(t_token *curr_token, t_data *data)
{
	if (!add_command_node(&data->cmd))
		return (false);
	if (!fill_command(curr_token, data))
		return (false);
	return (true);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*curr;
	
	curr = data->token;
	if (!add_command(curr, data))
	{
		free_cmd_list(&data->cmd);
		return (false);
	}
	curr = curr->next;
	while (curr != data->token)
	{
		if(curr->prev->type == PIPE && !add_command(curr, data))
		{
			free_cmd_list(&data->cmd);
			return (false);
		}
		curr = curr->next;
	}
	return (true);
}
