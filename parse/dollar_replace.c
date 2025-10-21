
#include "minishell.h"

//添加字符至输出字符串
// int	add_char()
// {
	
// }

/* 展开环境变量 成功1 失败0 */
int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int	ctrl;
	int	n;

	n = *index;
	ctrl = exist_in_env(line, index, data);
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n, str));
	// else if (ctrl == 2)
	// {

	// }
	// else
	// {

	// }
	return (0);
}

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = get_dollar_word(line, size);//malloc 要释放
	value = get_elem_env(data->env, key);//要释放
	if (key)
		free(key);
	tmp = ft_strjoin(*str, value);//要释放
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

int	replace_dollar(char **line, t_data *data)
{
	int		i;
	bool	dq;
	char	*str;

	i = 0;
	dq = false;
	data->sq = false;
	str = ft_strdup("");
	while((*line)[i])
	{
		quoting_choice(&dq, &data->sq, NULL, (*line)[i]);
		if ((*line)[i] && (*line)[i + 1] &&  (*line)[i] == '$' && \
			(*line)[i + 1] != '\'' && (*line)[i + 1] != '"' && \
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' || \
			(*line)[i + 1] == '_') && !data->sq && \
			!add_dollar((*line), &i, &str, data))
			return (0);
		// if ((*line)[i] && !add_char())
		// 	return (0);
	}
	free(*line);
	*line = str;
	return (1);
}
