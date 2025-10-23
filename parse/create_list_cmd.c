/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:39:48 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/23 16:04:53 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*create_new_command(t_cmd **new)
{
	(*new) = malloc(sizeof(t_cmd));
	if (!*new)
		return (NULL);
	(*new)->cmd_param = NULL;
	(*new)->infile = -2;
	(*new)->outfile = -2;
	(*new)->skip_cmd = false;
	(*new)->prev = NULL;
	(*new)->next = NULL;
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
		tmp->cmd_param = new;
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
	return (false);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*curr;
	
	curr = data->token;
	if (!add_command(&data->cmd))
	{
		free_command_list(data->cmd);
		return (false);
	}
	curr = curr->next;
	while (curr != data->token)
	{
		if(curr->type == CMD && !add_command(&data->cmd))
		{
			free_command_list(data->cmd);
			return (false);
		}
		curr = curr->next;
	}
	return (true);
}
