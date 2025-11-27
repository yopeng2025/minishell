#include "minishell.h"

static int	count_arg(t_data *data, t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (tmp->type == CMD || (tmp->type == ARG \
		&& tmp->prev != data->token->prev && tmp->prev->type > 5))
		i++;
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{	
		if (tmp->type == CMD || (tmp->type == ARG \
			&& tmp->prev != data->token->prev && tmp->prev->type > 5))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	add_to_cmd_param(char **cmd_param, int *i, char *str)
{
	cmd_param[*i] = ft_strdup(str);
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
		free(cmd_param[i]);
	}
	free(cmd_param);
	return (NULL);
}

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
	if (tmp->type != PIPE && (tmp->type == CMD || (tmp->type == ARG \
			&& tmp->prev != data->token->prev && tmp->prev->type > 5)) && \
			!add_to_cmd_param(cmd_param, &i, tmp->str))
		return (free_cmd_param(cmd_param, i));
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (tmp->type != PIPE && \
			(tmp->type == CMD || (tmp->type == ARG \
				&& tmp->prev != data->token->prev && tmp->prev->type > 5)) && \
				!add_to_cmd_param(cmd_param, &i, tmp->str))
			return (free_cmd_param(cmd_param, i));
		tmp = tmp->next;
	}
	cmd_param[i] = NULL;
	return (cmd_param);
}
