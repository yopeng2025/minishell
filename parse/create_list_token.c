/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:59:27 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/17 17:38:14 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//测试函数：打印所有的token
void	print_token_list(t_token *head)
{
    t_token *cur = head;
    int i = 0;

    printf("=== Token List ===\n");
    while (cur)
    {
        printf("Token %d: str='%s', prev=%p, next=%p\n",
               i,
               cur->str ? cur->str : "NULL",
            //    cur->type,
               (void *)cur->prev,
               (void *)cur->next);
        cur = cur->next;
        i++;
    }
    printf("==================\n");
}

void	free_token_list(t_token **head_token)
{
	t_token	*tmp;
	t_token	*curr;

	if (!head_token || !*head_token)
		return ;
	curr = *head_token;
	while (curr)
	{
		tmp = curr->next;
		free(curr->str);
		free(curr);
		curr = tmp;
	}
	*head_token = NULL;
}

t_token	*create_new_token(char *str)
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
	//need to add TYPE later!!
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
		return ;
	}
	tmp = *head_token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
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

bool	add_token(char **line, t_token **head_token)
{
	char	*str;
	int		lenth_token;
	t_token	*new;

	lenth_token = 0;
	while ((*line)[lenth_token] && !is_space((*line)[lenth_token]))
		lenth_token++;
	str = malloc(sizeof(char) * (lenth_token + 1));
	if (!str)
		return (false);
	cpy_str(str, *line, lenth_token);
	new = create_new_token(str);
	free(str);
	if (!new)
	{
		free_token_list(head_token);
		return (false);
	}
	add_new_back(head_token, new);
	*line += lenth_token;
	return (true);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'))
		return (true);
	return (false);
}

bool	create_list_token(t_token **head_token, char *line)
{
	while(*line)
	{
		while (is_space(*line))
			line++;
		if (!add_token(&line, head_token))
			free(line);
	}
	return (true);
}