#include "minishell.h"

void	cpy_str(char *str, char *line, int len)
{
	int	i;
	
	i = 0;
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

int	get_token_lenth(char **line)
{
	char	quote;
	int		lenth_token;

	lenth_token = 0;
	if (is_quote((*line)[0]))
	{
		quote = (*line)[0];
		(*line)++;
		while ((*line)[lenth_token] != quote)
			lenth_token++;
	}
	else
	{
		while ((*line)[lenth_token] && !is_space((*line)[lenth_token]))
			lenth_token++;
	}
	return (lenth_token);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'))
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