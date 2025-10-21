
#include "minishell.h"

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data))
	{
		free (line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	// if (!create_list_token(&data->token, line))
	// {
	// 	free(line);
	// 	return (false);
	// }
	return(true);
}
