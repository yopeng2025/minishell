/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:43 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:44 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_list_cmd(t_data *data)
{
	t_token	*curr;

	if (!check_syntax(data))
		return (false);
	curr = data->token;
	if (!add_command(curr, data))
		return (false);
	curr = curr->next;
	while (curr != data->token)
	{
		if (curr->prev->type == PIPE && !add_command(curr, data))
			return (false);
		curr = curr->next;
	}
	return (true);
}

bool	token_list(t_data *data, t_token **head_token, char *line)
{
	if (*line == '\0')
		return (false);
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (*line && !(is_special(line)) && !add_token(data, &line, head_token))
		{
			free(line);
			return (false);
		}
		else if (*line && is_special(line) && \
		!add_special(data, &line, head_token, is_special(line)))
		{
			free_token_list(head_token);
			free(line);
			return (false);
		}
	}
	if (*head_token == NULL)
		return (true);
	return (true);
}

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !token_list(data, &data->token, line))
	{
		free(line);
		return (false);
	}
	if (data->token->type == PIPE || data->token->prev->type == PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 51);
		free_token_list(&data->token);
		data->exit_code = 2;
		return (false);
	}
	free(line);
	if (!data->token || !create_list_cmd(data))
	{
		free_token_list(&data->token);
		free_cmd_list(&data->cmd);
		return (false);
	}
	return (true);
}
