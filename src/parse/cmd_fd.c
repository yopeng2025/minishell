/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:08:50 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/14 15:21:26 by peiyli           ###   ########.fr       */
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
	if (cmd->infile == -1)
		return (false);
	else
		return (true);
}

bool	get_out(t_token *curr_token, t_cmd *cmd, t_data *data)
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
	if (cmd->outfile == -1)
		return (false);
	else
		return (true);
}
