#include "minishell.h"

void	print_cmd_list(t_cmd *head)
{
	t_cmd *cur;

	cur = head;
	if (!head)
	{
		printf("=== Token List is EMPTY ===\n");
		return ;
	}
	printf("=== Token List (circular) ===\n");
	int i = 0;
	do
	{
		printf("[%d] fd_in=%d fd_out=%d\n",
			i, cur->infile, cur->outfile);
		cur = cur->next;
		i++;
	} while (cur != head);  // ✅ 循环回到起点就停止
	printf("============================\n");
}

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

bool	add_command(t_cmd **head_cmd)
{
	if (!add_command_node(head_cmd))
		return (false);
	// fill command
	return (true);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*curr;
	
	curr = data->token;
	if (!add_command(&data->cmd))
	{
		printf("add head\n");
		free_cmd_list(&data->cmd);
		return (false);
	}
	curr = curr->next;
	while (curr != data->token)
	{
		if(curr->type == CMD && !add_command(&data->cmd))
		{
			printf("add cmd\n");
			free_cmd_list(&data->cmd);
			return (false);
		}
		curr = curr->next;
	}
	return (true);
}
