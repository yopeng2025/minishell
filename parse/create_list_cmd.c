/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:39:48 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/23 12:41:33 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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