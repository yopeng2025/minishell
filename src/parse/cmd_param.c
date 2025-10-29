#include "minishell.h"

static int	count_arg(t_data *data, t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (tmp->type == CMD || (tmp->type == ARG \
		&& tmp->prev != data->token->prev && tmp->type >5))
		i++;
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{	
		if (tmp->type == CMD || (tmp->type == ARG \
			&& tmp->prev != data->token->prev && tmp->type >5))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	add_to_cmd_param(char **cmd_param, int *i, char *str)
{
	cmd_param[*i] = ft_strdup(str);//要释放
	if (!cmd_param[*i])
		return (0);
	(*i)++;
	return (1);
}

static void	*free_cmd_param(char **cmd_param, int i)
{
	if (!cmd_param)
		return (NULL);
	while (i > 0)
	{
		i--;
		free(cmd_param[i]); //释放数组元素
	}
	free(cmd_param); //释放数组本身cmd_param={"", "", "", NULL}
	return (NULL);
}

static void	print_cmd_param(char **cmd_param, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		printf("[debug]cmd[%i]: %s\n", j, cmd_param[j]);
		j++;
	}
}

/* 得到同一个管道内(非< << > >> |)的命令参数 cmd和arg */
char	**get_param(t_data *data, t_token *token)
{
	char	**cmd_param;
	t_token	*tmp;
	int		i;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_arg(data, token) + 1));
	if (!cmd_param)
		return (NULL);
	tmp = token;
	if (tmp->type != PIPE && \
		(tmp->type == CMD || (tmp->type == ARG \
			&& tmp->prev != data->token->prev && tmp->type >5)) && \
			!add_to_cmd_param(cmd_param, &i, tmp->str))
			return (free_cmd_param(cmd_param, i));
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (tmp->type != PIPE && \
			(tmp->type == CMD || (tmp->type == ARG \
				&& tmp->prev != data->token->prev && tmp->type >5)) && \
				!add_to_cmd_param(cmd_param, &i, tmp->str))
				return (free_cmd_param(cmd_param, i));
		tmp = tmp->next;
	}
	cmd_param[i] = NULL;
	print_cmd_param(cmd_param, i); //新增部分，用于检测是否成功提取命令参数
	return (cmd_param);
}
