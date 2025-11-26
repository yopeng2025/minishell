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

bool	handle_dollar_quote(char *line, int *i, t_data *data, bool dq)
{
	if (!line[*i] || !line[*i + 1])
		return (false);
	if ((line[*i] == '$' && line[*i + 1] == '"' && !dq) || \
		(line[*i] == '$' && line[*i + 1] == '\'' && !data->sq))
	{
		(*i)++;
		return (true);
	}
	else if ((line[*i] == '$' && line[*i + 1] == '"' && dq) || \
		(line[*i] == '$' && line[*i + 1] == '\'' && data->sq))
		return (false);
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
		if (!add_dollar(line, i, str, data))
			return (false);
		return (true);
	}
	return (false);
}

void	check_special_char(char **value)
{
	int		i;
	char	*new;

	i = 0;
	if (!value || !*value)
		return ;
	while ((*value)[i])
	{
		if ((*value)[i] == '|' || (*value)[i] == '<' || (*value)[i] == '>')
		{
			new = add_quote_special_char(*value);
			free(*value);
			*value = new;
			return ;
		}
		i++;
	}
}
