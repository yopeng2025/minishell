#include "minishell.h"

bool	add_command(t_cmd **head_cmd)
{
	if (!add_command_node(head_cmd))
		return (false);
	// fill command

	return (true);
}

bool	create_list_cmd(t_data *data)
{
	(void)*data;
		t_token	*curr;
	
	curr = data->token;
	if (!add_command(&data->cmd))
	{
		free_cmd_list(data->cmd);
		return (false);
	}
	while (curr != data->token)
	{
		if(curr->type == CMD && !add_command(&data->cmd))
		{
			free_cmd_list(data->cmd);
			return (false);
		}
		curr = curr->next;
	}
 	return (true);
}