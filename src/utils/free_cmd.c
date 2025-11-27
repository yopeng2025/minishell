/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:53 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:54 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
