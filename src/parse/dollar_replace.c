#include "minishell.h"

/* 成功1 失败0 输入：“exit code is: $?" 输出:"exit code is: 0"  */
static int	append_exit_code(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_code);//要释放
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	(*str) = tmp2;
	return (1); 
}

/* 添加字符至输出字符串 */
int	add_char(char *c, char **str, t_data *data, int *index)
{
	char	char_to_str[2];
	char	*tmp;
	int		i;

	i = 0;
	if (c[i] == '$' && !data->sq && exist_in_env(c, &i, data))
		return(1);
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = get_dollar_word(line, size);//malloc 要释放
	value = get_elem_env(data->env, key);//要释放
	fprintf(stderr, "[DEBUG] key=%s\n", key);							//用于检测是否正确展开，可删除
	fprintf(stderr, "[DEBUG] value=%s\n", value ? value : "(null)");    //用于检测是否正确展开，可删除
	if (key)
		free(key);
	tmp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

/* 展开环境变量 成功1 失败0（环境变量不存在时，index指针落在‘\0’ 或空格‘ ’等非_非字母上）*/
int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int	ctrl;
	int	n;

	n = *index;
	ctrl = exist_in_env(line, index, data);//指针在环境变量的后一位
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n, str));
	else if (ctrl == 2)
	{
		(*index) += 2;
		return (append_exit_code(data, str));
	}
	else
	{
		++(*index);
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			++(*index);
		return (1);
	}
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
		if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
		 	return (0);
	}
	*line = str;
	return (1);
}
