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
	free(line);
	return(true);
}
