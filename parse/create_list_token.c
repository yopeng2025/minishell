/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:59:27 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/23 11:35:48 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//测试函数：打印所有的token
void	print_token_list(t_token *head)
{
	t_token *cur;
	int i;

	if (!head)
	{
		printf("=== Token List is EMPTY ===\n");
		return ;
	}

	printf("=== Token List (circular) ===\n");
	cur = head;
	i = 0;
	do
	{
		printf("Token %d: str='%s', type=%d, prev=%p, next=%p\n",
			i,
			cur->str ? cur->str : "NULL",
			cur->type,
			(void *)cur->prev,
			(void *)cur->next);
		cur = cur->next;
		i++;
	} while (cur != head);  // ✅ 循环回到起点就停止
	printf("============================\n");
}

t_token	*create_new_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_new_back(t_token **head_token, t_token *new)
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

void	cpy_str(char *str, char *line , int len)
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

bool	add_token_node(t_token **head_token, char *str, int type)
{
	t_token	*new;
	
	new = create_new_token(str, type);
	if (!new)
	{
		free_token_list(head_token);
		return (false);
	}
	add_new_back(head_token, new);
	if (!new->type)
	{
		if (new->prev == new || new->prev->type == PIPE)
			new->type = CMD;
		else
			new->type = ARG;	
	}
	return (true);
}

bool	add_token(char **line, t_token **head_token)
{
	char	*str;
	int		lenth_token;

	lenth_token = get_token_lenth(line);
	str = malloc(sizeof(char) * (lenth_token + 1));
	if (!str)
		return (false);
	cpy_str(str, *line, lenth_token);
	if (!add_token_node(head_token, str, 0))
	{
		free(str);
		return (false);
	}
	free(str);
	*line += lenth_token;
	if (is_quote((*line)[0]))
		(*line)++;
	return (true);
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

bool	add_special_token(char **line, t_token **head_token, int type)
{
	if (type == INPUT && !add_token_node(head_token, ft_strdup("<"), INPUT))
		return (false);
	else if (type == TRUNCATE && !add_token_node(head_token, ft_strdup(">"), TRUNCATE))
		return (false);
	else if (type == HEREDOC && !add_token_node(head_token, ft_strdup("<<"), HEREDOC))
		return (false);
	else if (type == APPEND && !add_token_node(head_token, ft_strdup(">>"), APPEND))
		return (false);
	else if (type == PIPE && !add_token_node(head_token, ft_strdup("|"), PIPE))
		return (false);
	if (type == INPUT || type == TRUNCATE || type == PIPE)
		(*line)++;
	else if (type == HEREDOC || type == APPEND)
		*line += 2;
	return (true);
}

bool	create_list_token(t_token **head_token, char *line)
{
	while(*line)
	{
		while (is_space(*line))
			line++;
		if (*line && !(is_special(line)) && !add_token(&line, head_token))
		{
			free(line);
			return (false);
		}
		else if (*line && is_special(line) && !add_special_token(&line, head_token, is_special(line)))
		{
			free_token_list(head_token);
			free(line);
			return (false);
		}
		//check if the pipe is the !st or the end
	}
	return (true);
}
