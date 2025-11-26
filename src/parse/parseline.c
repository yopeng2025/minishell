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

static bool	handle_quotes(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !*(in_double))
	{
		*in_single = !*(in_single);
		return (true);
	}
	if (c == '"' && !*(in_single))
	{
		*in_double = !*(in_double);
		return (true);
	}
	return (false);
}

void	str_append_char(char **dst, char c)
{
	size_t	len;
	char	*new;

	len = ft_strlen(*dst);
	new = malloc(len + 2);
	if (!new)
		return ;
	if (*dst)
		ft_memcpy(new, *dst, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(*dst);
	*dst = new;
}


void	remove_quote(char **str, t_data *data)
{
	char	*new;
	bool	in_single = false;
	bool	in_double = false;
	int		i;

	new = ft_strdup("");
	if (!new)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	i = 0;
	while ((*str)[i])
	{
		if (handle_quotes((*str)[i], &in_single, &in_double))
		{
			i++;
			continue ;
		}
		str_append_char(&new, (*str)[i]);
		i++;
	}
	free(*str);
	*str = new;
}

bool	check_dollar(t_data *data)
{
	int		i;
	int		count;
	t_token	*tmp;

	count = count_token(data);
	i = 0;
	tmp = data->token;
	while (i < count)
	{
		replace_dollar(&(tmp->str), data);
		if (*(tmp->str) == '\0')
		{
			free_token_list(&data->token);
			return (false);
		}
		remove_quote(&(tmp->str), data);
		tmp = tmp->next;
		i++;
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
		!add_special_token(data, &line, head_token, is_special(line)))
		{
			free_token_list(head_token);
			free(line);
			return (false);
		}
	}
	if (*head_token == NULL)
		return (true);
	if (!check_dollar(data))
		return (false);
	return (true);
}

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (/*!replace_dollar(&line, data) ||*/ !token_list(data, &data->token, line))
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
	// print_token_list(data->token);
	free(line);
	if (!data->token || !create_list_cmd(data))
	{
		free_token_list(&data->token);
		free_cmd_list(&data->cmd);
		return (false);
	}
	// print_cmd_list(data->cmd);
	return (true);
}
