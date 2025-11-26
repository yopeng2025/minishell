#include "minishell.h"

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
	check_special_char(&value);
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
	while (line[*i + 1 + name_len] && \
		(ft_isalnum(line[*i + 1 + name_len]) || line[*i + 1 + name_len] == '_'))
		name_len++;
	return (name_len);
}

int	exist_in_env(char *line, int *i, t_data *data)
{
	t_list	*tmp;
	int		name_len;
	int		key_len;
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

int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int	ctrl;
	int	n;

	n = *index;
	ctrl = exist_in_env(line, index, data);
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
		(*index)++;
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			(*index)++;
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
	if (!str)
		return (0);
	while ((*line)[i])
	{
		quoting_choice(&dq, &data->sq, NULL, (*line)[i]);
		if (handle_dollar_digit(*line, &i, data))
			continue ;
		if (handle_dollar_quote(*line, &i, data, dq))
			continue ;
		if (handle_dollar_var(*line, &i, &str, data))
			continue ;
		if (!add_char(&(*line)[i], &str, &i))
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}
