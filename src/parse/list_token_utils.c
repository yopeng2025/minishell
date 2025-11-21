#include "minishell.h"

void	cpy_str(char *str, char *line, int len)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				str[j++] = line[i++];
			i++;
		}
		else
			str[j++] = line[i++];
	}
	str[j] = '\0';
}

static bool	handle_quotes(char c, bool *in_single, bool *in_double, int *quote)
{
	if (c == '\'' && !*(in_double))
	{
		*in_single = !*(in_single);
		(*quote)++;
		return (true);
	}
	if (c == '"' && !*(in_single))
	{
		*in_double = !*(in_double);
		(*quote)++;
		return (true);
	}
	return (false);
}

int	get_token_lenth(char *line, int *quote)
{
	int		i;
	bool	in_single;
	bool	in_double;

	(*quote) = 0;
	in_single = false;
	in_double = false;
	i = 0;
	while (line[i])
	{
		if (handle_quotes(line[i], &in_single, &in_double, quote))
		{
			i++;
			continue ;
		}
		if (!in_single && !in_double && (is_space(line[i]) \
			|| is_special(line + i)))
			break ;
		i++;
	}
	return (i);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r'))
		return (true);
	return (false);
}

int	is_special(char *line)
{
	if (line[0] == '|')
		return (PIPE);
	if (line[0] == '<')
	{
		if (line[1] == '<')
			return (HEREDOC);
		else
			return (INPUT);
	}
	if (line[0] == '>')
	{
		if (line[1] == '>')
			return (APPEND);
		else
			return (TRUNCATE);
	}
	return (0);
}
