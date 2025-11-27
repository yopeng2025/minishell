/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:30:48 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:30:49 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_token_exist(t_token *curr_token, t_data *data)
{
	char	*str;

	str = ft_strdup("minishell: syntax error near unexpected token 'newline'\n");
	if (curr_token->next == data->token)
	{
		write(2, str, ft_strlen(str));
		free(str);
		data->exit_code = 2;
		return (false);
	}
	else
	{
		free(str);
		return (true);
	}
}

bool	check_token_type(t_token *curr_token, t_data *data)
{
	if (curr_token->next->type <= 5)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		write(2, curr_token->next->str, ft_strlen(curr_token->next->str));
		write(2, "'\n", 2);
		data->exit_code = 2;
		return (false);
	}
	else
		return (true);
}

bool	check_syntax(t_data *data)
{
	t_token	*curr;

	curr = data->token;
	if (curr->type < 5)
	{
		if (!check_token_exist(curr, data))
			return (false);
		if (!check_token_type(curr, data))
			return (false);
	}
	curr = curr->next;
	while (curr != data->token)
	{
		if (curr->type < 5)
		{
			if (!check_token_exist(curr, data))
				return (false);
			if (!check_token_type(curr, data))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
