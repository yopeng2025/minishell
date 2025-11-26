#include "minishell.h"

/* 拼接一个字符到已有字符串 */
static char	*join_char(char *out, char c)
{
	char	*tmp;

	tmp = ft_strjoin_char(out, c);
	free(out);
	return (tmp);
}

/* 拼接一个特定的特殊符号 */
static char	*join_special(char *out, const char *s)
{
	char	*tmp;

	tmp = ft_strjoin(out, s);
	free(out);
	return (tmp);
}

/* 处理重定向 << 和 >> */
static int	handle_double_redir(char *str, int i, char **out)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		*out = join_special(*out, "\"<<\"");
		return (2);
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		*out = join_special(*out, "\">>\"");
		return (2);
	}
	return (0);
}

static void	process_char(char c, char **out)
{
	if (c == '<')
		*out = join_special(*out, "\"<\"");
	else if (c == '>')
		*out = join_special(*out, "\">\"");
	else if (c == '|')
		*out = join_special(*out, "\"|\"");
	else
		*out = join_char(*out, c);
}

/* 将字符串中所有特殊字符加上引号 */
char	*add_quote_special_char(char *str)
{
	char	*out;
	int		i;
	int		skip;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		skip = handle_double_redir(str, i, &out);
		if (skip)
		{
			i += skip;
			continue ;
		}
		process_char(str[i], &out);
		i++;
	}
	return (out);
}
