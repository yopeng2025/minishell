#include "minishell.h"

bool	create_list_token(t_token **head_token, char *line)
{
	while(*line)
	{
		while (is_space(*line))
			line++;
		if (*line && !(is_special(line)) && !add_token(&line, head_token))
		{
			free(line);
			return (false);
		}
		else if (*line && is_special(line) && !add_special_token(&line, head_token, is_special(line)))
		{
			free_token_list(head_token);
			free(line);
			return (false);
		}
	}
	if (*head_token == NULL)
		return (true);
	if ((*head_token)->type == PIPE || (*head_token)->prev->type == PIPE)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 51);
		return (false);
	}
	return (true);
}

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		free(line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	free(line);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		free_token_list(&data->token);
		return (false);
	}
	if (!data->token || !create_list_cmd(data))
	{
		free_token_list(&data->token);
		free_cmd_list(&data->cmd);
		return (false);
	}
//	print_cmd_list(data->cmd);
//	print_token_list(data->token);
	return(true);
}
