#include "minishell.h"

/* 成功1 失败0 输入：“exit code is: $?" 输出:"exit code is: 0"  */
static int	append_exit_code(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_code);
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

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = get_dollar_word(line, size);
	value = get_elem_env(data->env, key);
	if (key)
		free(key);
	if (!value)
		return (1);
	tmp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

static int	count_name_len(char *line, int *i)
{
	int		name_len;

	name_len = 0;
	while (line[*i + 1] + name_len && \
		(ft_isalnum(line[*i + 1 + name_len]) || line[*i + 1 + name_len] == '='))
		name_len++;
	return (name_len);
}

/*  1环境变量存在  2特殊变量？或者$  0不存在  同时移动index至字符串后一位*/
int	exist_in_env(char *line, int *i, t_data *data)
{
	t_list	*tmp;
	int		name_len; //$后的名字长度 $(name_len:len)
	int		key_len;  //环境变量名长度 (key_len:env)=home/yopeng
	int		list_len;

	if (line[*i + 1] == '?')
		return (2);
	name_len = count_name_len(line, i);
	tmp = data->env;
	list_len = len_list(tmp);
	while (list_len--)
	{
		key_len = ft_search(tmp->str, '=');
		if (key_len > 0 && key_len == name_len \
			&& ft_strncmp(tmp->str, &line[*i + 1], key_len) == 0)
		{
			*i += name_len + 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/* 展开环境变量 成功1 失败0（环境变量不存在时，index指针落在‘\0’ 或空格‘ ’等非_非字母上）*/
int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int	ctrl;
	int	n;

	n = *index;
	ctrl = exist_in_env(line, index, data);//指针在环境变量的后一位
	if (ctrl == 1)
	{
		in_env(data, &line[n], *index - n, str);
		return (1);
	}
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
