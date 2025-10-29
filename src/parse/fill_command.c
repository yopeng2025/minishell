/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:48:16 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/29 14:59:42 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_data *data, char *filename, int type)
{
	int	fd;
	
	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY);
	else if (type == HEREDOC)
		fd = here_doc(filename, data);
	else if (type == TRUNCATE)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

bool	get_in(t_token *curr_token, t_cmd *cmd, t_data *data)
{
	if (cmd->infile >= 0)
		close(cmd->cmd_param);
	if (curr_token->type <= 5)
		// erro notif
		return (false);
	if (curr_token->type == INPUT)
		cmd->infile = open_file(data, curr_token->str, INPUT);
	else if (curr_token->type == HEREDOC)
		cmd->infile = open_file(data, curr_token->str, HEREDOC);
	if (cmd->infile == -1)
		return (false);
	return (true);
}

bool	get_out(t_token *curr_token, t_cmd *cmd, t_data *data)
{
	if (cmd->outfile >= 0)
		close(cmd->cmd_param);
	if (curr_token->type <= 5)
		// erro notif
		return (false);
	if (curr_token->type == TRUNCATE)
		cmd->outfile = open_file(data, curr_token->str, TRUNCATE);
	else if (curr_token->type == APPEND)
		cmd->outfile = open_file(data, curr_token->str, APPEND);
	if (cmd->outfile == -1)
		return (false);
	return (true);
}

bool	get_infile(t_token *curr_token, t_cmd *cmd, t_data *data)
{
	if (curr_token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 40); // error notif
		return (false);
	}
	if (!get_in(curr_token, cmd, data))
		return (false);
	curr_token = curr_token->next;
	while (curr_token != PIPE || curr_token != data->token)
	{
		if (!get_in(curr_token, cmd, data))
			return (false);
		curr_token = curr_token->next;
	}
	return (true);
}

bool	get_outfile(t_token *curr_token, t_cmd *cmd, t_data *data)
{
	if (curr_token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 40); // error notif
		return (false);
	}
	if (!get_out(curr_token, cmd, data))
		return (false);
	curr_token = curr_token->next;
	while (curr_token != PIPE || curr_token != data->token)
	{
		if (!get_out(curr_token, cmd, data))
			return (false);
		curr_token = curr_token->next;
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
	data->cmd->cmd_param = get_param(data, curr_token);
	if (!data->cmd->cmd_param)
	// erro notif??
		return (false);
	return (true);
}
