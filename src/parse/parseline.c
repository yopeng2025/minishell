#include "minishell.h"

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		free (line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
		return (false);
	}
	free(line);										//++
	print_token_list(data->token);
	if (!create_list_cmd(data))
	{
		//需要free all吗？
		printf("ok\n");
		free_token_list(&data->token);
		return (false);
	}
	print_cmd_list(data->cmd);
	// printf("ok\n");
	return(true);
}
