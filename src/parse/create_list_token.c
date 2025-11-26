#include "minishell.h"

t_token	*create_new_token(t_data *data, char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->sq = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_new_token_back(t_token **head_token, t_token *new)
{
	t_token	*tmp;

	if (!*head_token)
	{	
		*head_token = new;
		new->prev = *head_token;
		new->next = *head_token;
		return ;
	}
	tmp = (*head_token)->prev;
	tmp->next = new;
	new->prev = tmp;
	new->next = *head_token;
	(*head_token)->prev = new;
}

bool	add_token_node(t_data *data, t_token **head_token, char *str, int type)
{
	t_token	*new;

	new = create_new_token(data, str, type);
	if (!new)
	{
		free_token_list(head_token);
		return (false);
	}
	free(str);
	add_new_token_back(head_token, new);
	if (!new->type)
	{
		if (new->prev == new || new->prev->type == PIPE)
			new->type = CMD;
		else
			new->type = ARG;
	}
	return (true);
}

void	put_str(char *str, char *line, int len)
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

bool	add_token(t_data *data, char **line, t_token **head_token)
{
	char	*str;
	// int		quote;
	int		lenth_token;

	lenth_token = get_token_length(*line);
	str = malloc(sizeof(char) * (lenth_token + 1));
	if (!str)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	put_str(str, *line, lenth_token);
	if (!add_token_node(data, head_token, str, 0))
	{
		free(str);
		return (false);
	}
	*line += lenth_token;
	return (true);
}

// bool	add_token(t_data *data, char **line, t_token **head_token)
// {
// 	char	*str;
// 	int		quote;
// 	int		lenth_token;

// 	lenth_token = get_token_lenth(*line, &quote);
// 	str = malloc(sizeof(char) * (lenth_token - quote + 1));
// 	if (!str)
// 		free_all(data, ERR_MALLOC, EXT_MALLOC);
// 	cpy_str(str, *line, lenth_token);
// 	if (!add_token_node(data, head_token, str, 0))
// 	{
// 		free(str);
// 		return (false);
// 	}
// 	*line += lenth_token;
// 	return (true);
// }

bool	add_special_token(t_data *data, char **line, t_token **head, int type)
{
	if (type == INPUT && !add_token_node(data, head, ft_strdup("<"), INPUT))
		return (false);
	else if (type == TRUNCATE && \
		!add_token_node(data, head, ft_strdup(">"), TRUNCATE))
		return (false);
	else if (type == HEREDOC && \
		!add_token_node(data, head, ft_strdup("<<"), HEREDOC))
		return (false);
	else if (type == APPEND && \
		!add_token_node(data, head, ft_strdup(">>"), APPEND))
		return (false);
	else if (type == PIPE && !add_token_node(data, head, ft_strdup("|"), PIPE))
		return (false);
	if (type == INPUT || type == TRUNCATE || type == PIPE)
		(*line)++;
	else if (type == HEREDOC || type == APPEND)
		*line += 2;
	return (true);
}
