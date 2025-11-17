#include "minishell.h"

bool	handle_dollar_digit(char *line, int *i, t_data *data)
{
	if (line[*i] && line[*i] == '$' \
		&& line[*i + 1] && ft_isdigit(line[*i + 1]) && !data->sq)
	{
		*i += 2;
		return (true);
	}
	return (false);
}

bool	handle_dollar_quote(char *line, int *i, t_data *data)
{
	if (!line[*i] || !line[*i + 1])
		return (false);
	if (line[*i] == '$' && line[*i + 1] == '"' && !data->sq)
	{
		if (line[*i + 2] && line[*i + 2] != '"')
		{
			(*i)++;
			return (true);
		}
		return (false);
	}
	return (false);
}

bool	handle_dollar_var(char *line, int *i, char **str, t_data *data)
{
	char	next;

	next = line[*i + 1];
	if (line[*i] && line[*i] == '$' && \
		(ft_isalpha(next) || next == '?' || next == '_') && \
		!data->sq)
	{
		if(!add_dollar(line, i, str, data))
			return (false);
		return (true);
	}
	return (false);
}
