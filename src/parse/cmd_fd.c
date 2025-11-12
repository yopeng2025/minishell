/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:08:50 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/12 14:22:59 by yopeng           ###   ########.fr       */
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
	if (curr_token->type == INPUT || curr_token->type == HEREDOC)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (curr_token->next->type <= 5)
		{
			write(2, "minishell: syntax error near unexpected token '", 47);	// erro notif
			write(2, curr_token->next->str, ft_strlen(curr_token->next->str));	// erro notif
			write(2, "'\n", 2);	// erro notif
			return (false);
		}
		if (curr_token->type == INPUT)
			cmd->infile = open_file(data, curr_token->next->str, INPUT);
		else if (curr_token->type == HEREDOC)
			cmd->infile = open_file(data, curr_token->next->str, HEREDOC);
		else
			return (true);
		if (cmd->infile == -1)
			return (false);
	}
	return (true);
}

bool	get_out(t_token *curr_token, t_cmd *cmd, t_data *data)
{
	if (curr_token->type == APPEND || curr_token->type == TRUNCATE)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (curr_token->next->type <= 5)
		{
			write(2, "minishell: syntax error near unexpected token '", 47);	// erro notif
			write(2, curr_token->next->str, ft_strlen(curr_token->next->str));	// erro notif
			write(2, "'\n", 2);	// erro notif
			return (false);
		}
		if (curr_token->type == TRUNCATE)
			cmd->outfile = open_file(data, curr_token->next->str, TRUNCATE);
		else if (curr_token->type == APPEND)
			cmd->outfile = open_file(data, curr_token->next->str, APPEND);
		else
			return (true);
		if (cmd->outfile == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_token *curr_token, t_cmd *cmd, t_data *data)
{
	if (curr_token->type == PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50); // error notif
		return (false);
	}
	if (!get_in(curr_token, cmd, data))
		return (false);
	curr_token = curr_token->next;
	while (curr_token->type != PIPE && curr_token != data->token)
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
		write(2, "minishell: syntax error near unexpected token '|'\n", 50); // error notif
		return (false);
	}
	if (!get_out(curr_token, cmd, data))
		return (false);
	curr_token = curr_token->next;
	while (curr_token->type != PIPE && curr_token != data->token)
	{
		if (!get_out(curr_token, cmd, data))
			return (false);
		curr_token = curr_token->next;
	}
	return (true);
}
