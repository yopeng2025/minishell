#include "minishell.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

static int	end_word(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	if (i == ft_search(env, '='))
		return (i);
	return (0);
}

/*  1环境变量存在  2特殊变量？或者$  0不存在  */
int	exist_in_env(char *line, int *i, t_data *data)
{
	t_list	*tmp;
	int		len;

	if (line[*i + 1] == '?' || line[*i + 1] == '$')
		return (2);
	tmp = data->env;
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->str, &line[*i + 1], \
			end_word(&line[*i + 1], tmp->str)) == 0)
		{
			*i += ft_strlen(tmp->str) - \
				ft_strlen(ft_strchr(tmp->str, '=')) + 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/* 取出环境变量名 */
char	*get_dollar_word(char *line, int size)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * size);//要释放
	if (!word)
		return (NULL);
	i = 0;
	while (line[++i] && i < size)
		word[i - 1] = line[i];
	word[i - 1] = '\0';
	return (word);
}

/*  取出环境变量的内容（即‘=’后面的内容） */
char	*get_elem_env(t_list *env, char *key)
{
	t_list	*tmp;
	int		list_len;
	int		key_len;
	int		i;

	if (!key)
		return (NULL);
	tmp = env;
	list_len = len_list(tmp);
	key_len = ft_strlen(key);
	while(list_len--)
	{
		if (ft_strncmp(tmp->str, key, key_len) == 0 && \
			tmp->str[key_len] == '=')
		{
			i = 0;
			while(tmp->str[i] && tmp->str[i] != '=')
				i++;
			return (ft_strdup(&tmp->str[i + 1])); //要释放
		}
		tmp = tmp->next;
	}
	return (NULL);
}

